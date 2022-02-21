// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Copyright (c) 2018-2020 Whive Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_WALLET_RPCWALLET_H
#define BITCOIN_WALLET_RPCWALLET_H

#include <string>

class CRPCTable;
class CWallet;
class JSONRPCRequest;
class LegacyScriptPubKeyMan;
class UniValue;
struct PartiallySignedTransaction;
class CTransaction;

namespace interfaces {
class Chain;
class Handler;
}

//! Pointer to chain interface that needs to be declared as a global to be
//! accessible loadwallet and createwallet methods. Due to limitations of the
//! RPC framework, there's currently no direct way to pass in state to RPC
//! methods without globals.
extern interfaces::Chain* g_rpc_chain;

void RegisterWalletRPCCommands(interfaces::Chain& chain, std::vector<std::unique_ptr<interfaces::Handler>>& handlers);

/**
 * Figures out what wallet, if any, to use for a JSONRPCRequest.
 *
 * @param[in] request JSONRPCRequest that wishes to access a wallet
 * @return nullptr if no wallet should be used, or a pointer to the CWallet
 */
std::shared_ptr<CWallet> GetWalletForJSONRPCRequest(const JSONRPCRequest& request);

void EnsureWalletIsUnlocked(const CWallet*);
bool EnsureWalletIsAvailable(const CWallet*, bool avoidException);
LegacyScriptPubKeyMan& EnsureLegacyScriptPubKeyMan(CWallet& wallet, bool also_create = false);

UniValue getaddressinfo(const JSONRPCRequest& request);
UniValue signrawtransactionwithwallet(const JSONRPCRequest& request);
bool FillPSBT(const CWallet* pwallet, PartiallySignedTransaction& psbtx, int sighash_type = 1 /* SIGHASH_ALL */, bool sign = true, bool bip32derivs = false);
#endif //BITCOIN_WALLET_RPCWALLET_H
