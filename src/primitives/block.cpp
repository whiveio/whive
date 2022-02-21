// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2018-2022 Whive Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>

#include <hash.h>
#include <tinyformat.h>
#include <crypto/common.h>
#include <hashdb.h>

extern "C" void yespower_hash(const void *input, void *output);

uint256 CBlockHeader::GetHash() const
{
    uint256 hash;
    if (phashdb) {
        if(!phashdb->Read(*this, hash)) {
            yespower_hash(BEGIN(nVersion), &hash);
            phashdb->Write(*this, hash);
        }
    } else {
        yespower_hash(BEGIN(nVersion), &hash);
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
