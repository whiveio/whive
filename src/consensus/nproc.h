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

/** Optimization Weights **/
static const float STAKE_WEIGHT = 3/10;
static const float PROCESSOR_WEIGHT = 3/10;
static const float TIMEZONE_WEIGHT = 1/10;
static const float LOCATION_WEIGHT = 3/10;

#endif // BITCOIN_CONSENSUS_NPROC_H
