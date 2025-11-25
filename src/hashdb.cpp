// Copyright (c) 2018-2019 Whive Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <hashdb.h>
#include <hash.h>
#include <logging.h>

std::unique_ptr<CHashDB> phashdb;

CHashDB::CHashDB(size_t nCacheSize, bool fMemory, bool fWipe) :
       CDBWrapper{DBParams{
             .path = gArgs.GetDataDirNet() / "hashes",
             .cache_bytes = nCacheSize,
             .memory_only = fMemory,
             .wipe_data = fWipe}}
{
}

// Disabled for now - causes deadlock during block loading
// TODO: Implement proper async caching without deadlock
/*
uint256 CHashDB::GetHash(const CBlockHeader &block)
{
    uint256 hash;

    // Try to read from cache first
    if (Read(block, hash)) {
        return hash;
    }

    // Cache miss - compute the hash
    hash = SerializeHashYespower(block);

    // Store in cache for future use
    // Use try-catch to avoid blocking if DB is busy
    try {
        Write(block, hash);
    } catch (...) {
        // Ignore write errors - cache is optional
    }

    return hash;
}
*/
