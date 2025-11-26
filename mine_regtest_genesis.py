#!/usr/bin/env python3
"""
Mine new RegTest genesis block for Whive with 200 COIN reward
"""
import hashlib
import struct
import sys

def serialize_block_header(version, prev_block, merkle_root, timestamp, bits, nonce):
    """Serialize block header for hashing"""
    header = struct.pack("<I", version)
    header += bytes.fromhex(prev_block)[::-1]
    header += bytes.fromhex(merkle_root)[::-1]
    header += struct.pack("<I", timestamp)
    header += struct.pack("<I", bits)
    header += struct.pack("<I", nonce)
    return header

def calculate_merkle_root_from_tx(coinbase_tx_hex):
    """Calculate merkle root from transaction"""
    tx_bytes = bytes.fromhex(coinbase_tx_hex)
    hash1 = hashlib.sha256(tx_bytes).digest()
    hash2 = hashlib.sha256(hash1).digest()
    return hash2[::-1].hex()

# Genesis block parameters from CreateGenesisBlock
# CreateGenesisBlock(1296688602, 2, 0x207fffff, 1, 200 * COIN)
VERSION = 1
PREV_BLOCK = "0" * 64
TIMESTAMP = 1296688602
BITS = 0x207fffff
NONCE_START = 0

# Need to calculate merkle root for 200 COIN coinbase
# The coinbase transaction changes when reward changes from 50 to 200 COIN

print("Mining RegTest genesis block with 200 COIN reward...")
print(f"Timestamp: {TIMESTAMP}")
print(f"Bits: 0x{BITS:08x}")
print()

# For regtest with 0x207fffff difficulty, should mine quickly
# We need the actual merkle root from a 200 COIN coinbase transaction

# The merkle root will be different because the coinbase output value changed
# We need to look at what CreateGenesisBlock produces with 200 COIN

print("NOTE: The actual merkle root must be calculated from CreateGenesisBlock")
print("with 200 * COIN parameter. Let's use a simpler approach:")
print()
print("1. Temporarily comment out the assert() statements in chainparams.cpp")
print("2. Build whived")
print("3. Run: whived -regtest -printtoconsole")
print("4. It will print the actual genesis hash and merkle root")
print("5. Copy those values back into chainparams.cpp")
print()
print("This is safer than trying to recalculate the merkle root manually.")
