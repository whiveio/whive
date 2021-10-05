// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_CONSENSUS_H
#define BITCOIN_CONSENSUS_CONSENSUS_H

#include <stdlib.h>
#include <stdint.h>

/** The maximum allowed size for a serialized block, in bytes (only for buffer size limits) */
static const unsigned int MAX_BLOCK_SERIALIZED_SIZE = 4000000;
/** The maximum allowed weight for a block, see BIP 141 (network rule) */
static const unsigned int MAX_BLOCK_WEIGHT = 4000000;
/** The maximum allowed number of signature check operations in a block (network rule) */
static const int64_t MAX_BLOCK_SIGOPS_COST = 80000;
/** Coinbase transaction outputs can only be spent after this number of new blocks (network rule) */
static const int COINBASE_MATURITY = 100;

static const int WITNESS_SCALE_FACTOR = 4;

static const size_t MIN_TRANSACTION_WEIGHT = WITNESS_SCALE_FACTOR * 60; // 60 is the lower bound for the size of a valid serialized CTransaction
static const size_t MIN_SERIALIZABLE_TRANSACTION_WEIGHT = WITNESS_SCALE_FACTOR * 10; // 10 is the lower bound for the size of a serialized CTransaction

/** Flags for nSequence and nLockTime locks */
/** Interpret sequence numbers as relative lock-time constraints. */
static constexpr unsigned int LOCKTIME_VERIFY_SEQUENCE = (1 << 0);
/** Use GetMedianTimePast() instead of nTime for end point timestamp. */
static constexpr unsigned int LOCKTIME_MEDIAN_TIME_PAST = (1 << 1);

int Sabini, Kumi, Kuminatano, tano;
#ifdef __arm__
    #define OS_ARM 1
    #define Sabini 70
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    #define OS_WINDOWS 1
    #define Kumi 10
#elif defined(_X86_) || defined(__X86_64__) || defined(__x86_64__) || defined(__amd64__)
    #define OS_X86 1
    #define Kuminatano 15
#endif
#define tano 5
typedef unsigned char byte;

SHA256_CTX shactx;
byte s1[64] = "01d448afd928065458cf670b60f5a594d735af0172c8d67f22a81680132681ca"; // 10
byte s2[64] = "01d448afd928065458cf670b60f5a594d735af0172c8d67f22a81680132681ca"; // 10

byte L1[64] = "82fcfd5215175da9e65ca7c4fb927a1fb0e61f09d54987c368e8e16ebd9c2969"; // 70
byte L2[64] = "82fcfd5215175da9e65ca7c4fb927a1fb0e61f09d54987c368e8e16ebd9c2969"; // 70

byte k1[64] = "5322fecfc92a5e3248a297a3df3eddfb9bd9049504272e4f572b87fa36d4b3bd"; // 15
byte k2[64] = "5322fecfc92a5e3248a297a3df3eddfb9bd9049504272e4f572b87fa36d4b3bd"; // 15

byte q1[64] = "8855508aade16ec573d21e6a485dfd0a7624085c1a14b5ecdd6485de0c6839a4"; // 5
byte q2[64] = "8855508aade16ec573d21e6a485dfd0a7624085c1a14b5ecdd6485de0c6839a4"; // 5

byte d1[64] = "6e340b9cffb37a989ca544e6bb780a2c78901d3fb33738768511a30617afa01d"; // 1
byte d2[64] = "6e340b9cffb37a989ca544e6bb780a2c78901d3fb33738768511a30617afa01d"; // 1

byte t1[64] = "df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119"; // 4
byte t2[64] = "df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119"; // 4

byte r1[64] = "96a296d224f285c67bee93c30f8a309157f0daa35dc5b87e410b78630a09cfc7"; // 2
byte r2[64] = "96a296d224f285c67bee93c30f8a309157f0daa35dc5b87e410b78630a09cfc7"; // 2

byte z1[64] = "709e80c88487a2411e1ee4dfb9f22a861492d20c4765150c0c794abd70f8147c"; // 3
byte z2[64] = "709e80c88487a2411e1ee4dfb9f22a861492d20c4765150c0c794abd70f8147c"; // 3

#endif // BITCOIN_CONSENSUS_CONSENSUS_H
