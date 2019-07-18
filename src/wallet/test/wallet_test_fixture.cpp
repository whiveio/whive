// Copyright (c) 2016-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <wallet/test/wallet_test_fixture.h>

<<<<<<< HEAD
#include <rpc/server.h>
#include <wallet/db.h>

WalletTestingSetup::WalletTestingSetup(const std::string& chainName):
    TestingSetup(chainName), m_wallet("mock", WalletDatabase::CreateMock())
=======
WalletTestingSetup::WalletTestingSetup(const std::string& chainName)
    : TestingSetup(chainName),
      m_wallet(m_chain.get(), WalletLocation(), WalletDatabase::CreateMock())
>>>>>>> upstream/master
{
    bool fFirstRun;
    m_wallet.LoadWallet(fFirstRun);
    RegisterValidationInterface(&m_wallet);

    RegisterWalletRPCCommands(tableRPC);
}

WalletTestingSetup::~WalletTestingSetup()
{
    UnregisterValidationInterface(&m_wallet);
}
