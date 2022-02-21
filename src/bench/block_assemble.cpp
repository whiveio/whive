// Copyright (c) 2011-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <bench/bench.h>
#include <chainparams.h>
#include <coins.h>
#include <consensus/merkle.h>
#include <consensus/validation.h>
#include <crypto/sha256.h>
#include <test/util/mining.h>
#include <test/util/setup_common.h>
#include <test/util/wallet.h>
#include <txmempool.h>
#include <utiltime.h>
#include <validation.h>
#include <validationinterface.h>

#include <boost/thread.hpp>

#include <vector>

static void AssembleBlock(benchmark::Bench& bench)
{
    TestingSetup test_setup{
        CBaseChainParams::REGTEST,
        /* extra_args */ {
            "-nodebuglogfile",
            "-nodebug",
        },
    };

    const std::vector<unsigned char> op_true{OP_TRUE};
    CScriptWitness witness;
    witness.stack.push_back(op_true);

    uint256 witness_program;
    CSHA256().Write(&op_true[0], op_true.size()).Finalize(witness_program.begin());

    const CScript SCRIPT_PUB{CScript(OP_0) << std::vector<unsigned char>{witness_program.begin(), witness_program.end()}};

    // Switch to regtest so we can mine faster
    // Also segwit is active, so we can include witness transactions
    SelectParams(CBaseChainParams::REGTEST);

    InitScriptExecutionCache();

    boost::thread_group thread_group;
    CScheduler scheduler;
    {
        ::pblocktree.reset(new CBlockTreeDB(1 << 20, true));
        ::pcoinsdbview.reset(new CCoinsViewDB(1 << 23, true));
        ::pcoinsTip.reset(new CCoinsViewCache(pcoinsdbview.get()));

        const CChainParams& chainparams = Params();
        thread_group.create_thread(boost::bind(&CScheduler::serviceQueue, &scheduler));
        GetMainSignals().RegisterBackgroundSignalScheduler(scheduler);
        LoadGenesisBlock(chainparams);
        CValidationState state;
        ActivateBestChain(state, chainparams);
        assert(::chainActive.Tip() != nullptr);
        const bool witness_enabled{IsWitnessEnabled(::chainActive.Tip(), chainparams.GetConsensus())};
        assert(witness_enabled);
    }

    // Collect some loose transactions that spend the coinbases of our mined blocks
    constexpr size_t NUM_BLOCKS{200};
    std::array<CTransactionRef, NUM_BLOCKS - COINBASE_MATURITY + 1> txs;
    for (size_t b{0}; b < NUM_BLOCKS; ++b) {
        CMutableTransaction tx;
        tx.vin.push_back(MineBlock(test_setup.m_node, SCRIPT_PUB));
        tx.vin.back().scriptWitness = witness;
        tx.vout.emplace_back(1337, SCRIPT_PUB);
        if (NUM_BLOCKS - b >= COINBASE_MATURITY)
            txs.at(b) = MakeTransactionRef(tx);
    }
    {
        LOCK(::cs_main); // Required for ::AcceptToMemoryPool.

        for (const auto& txr : txs) {
            TxValidationState state;
            bool ret{::AcceptToMemoryPool(*test_setup.m_node.mempool, state, txr, nullptr /* plTxnReplaced */, false /* bypass_limits */)};
            assert(ret);
        }
    }

    bench.run([&] {
        PrepareBlock(test_setup.m_node, SCRIPT_PUB);
    });
}

BENCHMARK(AssembleBlock);
