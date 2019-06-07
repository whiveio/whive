// Copyright (c) 2015-2018 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chain.h>
#include <chainparams.h>
#include <pow.h>
#include <random.h>
#include <util.h>
#include <test/test_bitcoin.h>

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(pow_tests, BasicTestingSetup)

/* Test calculation of next difficulty target with DGW */
BOOST_AUTO_TEST_CASE(get_next_work)
{
    SelectParams(CBaseChainParams::MAIN);
    const Consensus::Params& params = Params().GetConsensus();

    // build the chain of 12 blocks
    CBlockIndex blockIndexLast;
    blockIndexLast.nHeight = 123456;
    blockIndexLast.nTime = 1408732489;
    blockIndexLast.nBits = 0x1b1418d4;
    CBlockIndex blockIndexPrev1 = CBlockIndex();
    blockIndexPrev1.nTime = 1408732257;  // Block #123455
    blockIndexPrev1.nBits = 0x1b13b83f;
    blockIndexLast.pprev = &blockIndexPrev1;
    CBlockIndex blockIndexPrev2 = CBlockIndex();
    blockIndexPrev2.nTime = 1408732229;  // Block #123454
    blockIndexPrev2.nBits = 0x1b10460b;
    blockIndexPrev1.pprev = &blockIndexPrev2;
    CBlockIndex blockIndexPrev3 = CBlockIndex();
    blockIndexPrev3.nTime = 1408731256;  // Block #123453
    blockIndexPrev3.nBits = 0x1b113ff1;
    blockIndexPrev2.pprev = &blockIndexPrev3;
    CBlockIndex blockIndexPrev4 = CBlockIndex();
    blockIndexPrev4.nTime = 1408731242;  // Block #123452
    blockIndexPrev4.nBits = 0x1b0fed89;
    blockIndexPrev3.pprev = &blockIndexPrev4;
    CBlockIndex blockIndexPrev5 = CBlockIndex();
    blockIndexPrev5.nTime = 1408730914;  // Block #123451
    blockIndexPrev5.nBits = 0x1b10b864;
    blockIndexPrev4.pprev = &blockIndexPrev5;
    CBlockIndex blockIndexPrev6 = CBlockIndex();
    blockIndexPrev6.nTime = 1408730862;  // Block #123450
    blockIndexPrev6.nBits = 0x1b0dd168;
    blockIndexPrev5.pprev = &blockIndexPrev6;
    CBlockIndex blockIndexPrev7 = CBlockIndex();
    blockIndexPrev7.nTime = 1408730179;  // Block #123449
    blockIndexPrev7.nBits = 0x1b0c03d6;
    blockIndexPrev6.pprev = &blockIndexPrev7;
    CBlockIndex blockIndexPrev8 = CBlockIndex();
    blockIndexPrev8.nTime = 1408729678;  // Block #123448
    blockIndexPrev8.nBits = 0x1b0c9ab8;
    blockIndexPrev7.pprev = &blockIndexPrev8;
    CBlockIndex blockIndexPrev9 = CBlockIndex();
    blockIndexPrev9.nTime = 1408729647;  // Block #123447
    blockIndexPrev9.nBits = 0x1b0dfaff;
    blockIndexPrev8.pprev = &blockIndexPrev9;
    CBlockIndex blockIndexPrev10 = CBlockIndex();
    blockIndexPrev10.nTime = 1408729587;  // Block #123446
    blockIndexPrev10.nBits = 0x1b10e878;
    blockIndexPrev9.pprev = &blockIndexPrev10;
    CBlockIndex blockIndexPrev11 = CBlockIndex();
    blockIndexPrev11.nTime = 1408729576;  // Block #123445
    blockIndexPrev11.nBits = 0x1b1063d0;
    blockIndexPrev10.pprev = &blockIndexPrev11;
    CBlockIndex blockIndexPrev12 = CBlockIndex();
    blockIndexPrev12.nTime = 1408729474;  // Block #123444
    blockIndexPrev12.nBits = 0x1b104297;
    blockIndexPrev11.pprev = &blockIndexPrev12;

    CBlockHeader blockHeader;
    blockHeader.nTime = 1408732505; // Block #123457
    BOOST_CHECK_EQUAL(GetNextWorkRequired(&blockIndexLast, &blockHeader, params), 0x1b2fed0e); // Block #123457 has 0x1b1441de
}

BOOST_AUTO_TEST_CASE(GetBlockProofEquivalentTime_test)
{
    const auto chainParams = CreateChainParams(CBaseChainParams::MAIN);
    std::vector<CBlockIndex> blocks(10000);
    for (int i = 0; i < 10000; i++) {
        blocks[i].pprev = i ? &blocks[i - 1] : nullptr;
        blocks[i].nHeight = i;
        blocks[i].nTime = 1269211443 + i * chainParams->GetConsensus().nPowTargetSpacing;
        blocks[i].nBits = 0x207fffff; /* target 0x7fffff000... */
        blocks[i].nChainWork = i ? blocks[i - 1].nChainWork + GetBlockProof(blocks[i - 1]) : arith_uint256(0);
    }

    for (int j = 0; j < 1000; j++) {
        CBlockIndex *p1 = &blocks[InsecureRandRange(10000)];
        CBlockIndex *p2 = &blocks[InsecureRandRange(10000)];
        CBlockIndex *p3 = &blocks[InsecureRandRange(10000)];

        int64_t tdiff = GetBlockProofEquivalentTime(*p1, *p2, *p3, chainParams->GetConsensus());
        BOOST_CHECK_EQUAL(tdiff, p1->GetBlockTime() - p2->GetBlockTime());
    }
}

BOOST_AUTO_TEST_SUITE_END()
