// Copyright (c) 2017-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_RPC_UTIL_H
#define BITCOIN_RPC_UTIL_H

#include <node/transaction.h>
#include <outputtype.h>
#include <pubkey.h>
#include <script/standard.h>
#include <univalue.h>

#include <boost/variant/static_visitor.hpp>

#include <string>
#include <vector>

class CKeyStore;
class CPubKey;
class CScript;

CPubKey HexToPubKey(const std::string& hex_in);
CPubKey AddrToPubKey(CKeyStore* const keystore, const std::string& addr_in);
CTxDestination AddAndGetMultisigDestination(const int required, const std::vector<CPubKey>& pubkeys, OutputType type, CKeyStore& keystore, CScript& script_out);

UniValue DescribeAddress(const CTxDestination& dest);

#endif // BITCOIN_RPC_UTIL_H
