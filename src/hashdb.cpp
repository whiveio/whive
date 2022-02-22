// Copyright (c) 2018-2019 Whive Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <hashdb.h>

std::unique_ptr<CHashDB> phashdb;

CHashDB::CHashDB(size_t nCacheSize, bool fMemory, bool fWipe) : CDBWrapper(GetDataDir() / "hashes", nCacheSize, fMemory, fWipe) {
}
