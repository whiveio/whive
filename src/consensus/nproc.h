// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_NPROC_H
#define BITCOIN_CONSENSUS_NPROC_H

#include <stdlib.h>
#include <stdint.h>

/** Number of processors allowed */
static const int NPROCS = 2;
static const int NPROCS_MAX = 4;

/** Optimization Weights (@qwainaina) **/
static const int STAKE_WEIGHT = 3;
static const int PROCESSOR_WEIGHT = 3;
static const int TIMEZONE_WEIGHT = 1;
static const int LOCATION_WEIGHT = 3;
static const int DIVISOR = 10;
static const int UPPER_LIMIT = 75;

#endif // BITCOIN_CONSENSUS_NPROC_H
