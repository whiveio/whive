// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2018-2022 Whive Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>

#include <hash.h>
#include <tinyformat.h>
#include <util/strencodings.h>
#include <crypto/common.h>
#include <hashdb.h>
#include <streams.h>
#include <pow.h>
#include <sync.h>

uint256 CBlockHeader::GetHash() const
{
    uint256 hash;
    if (phashdb) {
        // Use hashdb cache if available
        if (!phashdb->Read(*this, hash)) {
            // Cache miss - compute and store
            hash = SerializeHashYespower(*this);
            phashdb->Write(*this, hash);
        }
    } else {
        // Hashdb not initialized yet (during block index loading)
        // Compute hash directly without caching
        hash = SerializeHashYespower(*this);
    }
    return hash;
}


std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}
