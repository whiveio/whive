// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_NPROC_H
#define BITCOIN_CONSENSUS_NPROC_H

#include <stdlib.h>
#include <stdint.h>
#include <openssl/sha.h>
#ifdef _WIN32
 #include <windows.h>
#else
 #include <sys/sysinfo.h>
 #define  nl  get_nprocs()
 #define  nc  get_nprocs_conf()
#endif

/** Optimization Weights (@qwainaina) **/
static const int PROCESSOR_WEIGHT = 7;
static const int STAKE_WEIGHT = 6;
static const int LOCATION_WEIGHT = 2; // reduced until oracle hardened
static const int TIMEZONE_WEIGHT = 5;

static const int DIVISOR = 20;

static const int UPPER_LIMIT = 75;

static const int BALANCE_DIVISOR = 2500000;

static const float DEFAULT_LAT = -82.8628;
static const float DEFAULT_LON =  135.0000;

typedef unsigned char byte;

SHA256_CTX shactx;
byte qqq3[66] = "8855508aade16ec573d21e6a485dfd0a7624085c1a14b5ecdd6485de0c6839a4";  // 5
byte sss2[66] = "01d448afd928065458cf670b60f5a594d735af0172c8d67f22a81680132681ca"; // 10
byte LLL2[66] = "82fcfd5215175da9e65ca7c4fb927a1fb0e61f09d54987c368e8e16ebd9c2969"; // 70
byte kkk2[66] = "5322fecfc92a5e3248a297a3df3eddfb9bd9049504272e4f572b87fa36d4b3bd"; // 15
byte qqq2[66] = "8855508aade16ec573d21e6a485dfd0a7624085c1a14b5ecdd6485de0c6839a4"; // 5
byte ddd2[66] = "6e340b9cffb37a989ca544e6bb780a2c78901d3fb33738768511a30617afa01d"; // 1
byte ttt2[66] = "df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119"; // 4
byte rrr2[66] = "96a296d224f285c67bee93c30f8a309157f0daa35dc5b87e410b78630a09cfc7"; // 2
byte zzz2[66] = "709e80c88487a2411e1ee4dfb9f22a861492d20c4765150c0c794abd70f8147c"; // 3



#ifdef __arm__
    #define OS_ARM 1   
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    #define OS_WINDOWS 1   
#elif defined(_X86_) || defined(__X86_64__) || defined(__x86_64__) || defined(__amd64__)
    #define OS_X86 1   
#endif

#define Kuminatano 15
#define Kumi 10
#define Sabini 70
#define tano 5

#endif // BITCOIN_CONSENSUS_NPROC_H
