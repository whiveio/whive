// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_NPROC_H
#define BITCOIN_CONSENSUS_NPROC_H

#include <stdlib.h>
#include <stdint.h>
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

#endif // BITCOIN_CONSENSUS_NPROC_H
