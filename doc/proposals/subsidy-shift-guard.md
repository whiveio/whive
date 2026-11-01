# Proposal: make the block subsidy defined after 64 halvings

**Proposal only.** This touches consensus. It changes no code, and nothing here
is authorized for implementation, release or activation. The maintainers decide.

Reviewed source: tag `22.2.2` (`56ccfb28c7b796506ae371c6abff7c9a729ea067`),
`src/validation.cpp:1187-1198`.

## The problem

```cpp
int halvings = nHeight / consensusParams.nSubsidyHalvingInterval;
// Force block reward to zero when right shift is undefined.
if (halvings >= 100)
    return 0;

CAmount nSubsidy = 200 * COIN;
nSubsidy >>= halvings;
```

`CAmount` is a 64-bit signed integer. In C++, shifting it right by 64 or more
is undefined behaviour. The guard stops at 100, so halvings 64 to 99 shift by
an undefined amount. Bitcoin Core uses `halvings >= 64` here; the Whive value
appears to be a leftover from changing the constants.

With the 210,000-block interval, halving 64 starts at height 13,440,000. At the
10-minute target that is about 255 years after genesis. The heights are exact;
the date is only an estimate.

## What happens on real hardware

Undefined behaviour means the compiler may do anything. On common CPUs the
shift instruction uses only the low 6 bits of the count, so a shift by 64 acts
like a shift by 0. Measured on 2026-10-29 (arm64, Apple clang 14.0.3, `-O0` and
`-O2`), with a copy of the function above:

| Halving | Height | Current code | With `>= 64` |
|---|---|---|---|
| 35 to 63 | 7,350,000 to 13,439,999 | 0 | 0 |
| 64 | 13,440,000 | 20,000,000,000 (200 WHIVE) | 0 |
| 65 | 13,650,000 | 10,000,000,000 (100 WHIVE) | 0 |
| 98 | 20,580,000 | 1 | 0 |
| 100 and later | 21,000,000 and later | 0 | 0 |

UndefinedBehaviorSanitizer reports `shift exponent 64 is too large for 64-bit
type`. So on this machine the subsidy restarts at 200 WHIVE at halving 64 and
halves again until halving 99. Over halvings 64 to 98 that would issue about
84,000,000 WHIVE more (sum of `210000 * (200 * COIN >> k)` for k = 0 to 34).
Other compilers, CPUs or optimization levels may return different values, so
nodes could disagree and split.

x86-64 and other compilers were not measured.

## Proposed change

```cpp
if (halvings >= 64)
    return 0;
```

## Why this does not change any existing or near-future block

`200 * COIN` is 20,000,000,000, which is below 2^35. Any shift from 35 to 63 is
defined and gives 0. So for every height below 13,440,000 the current and
proposed code return the same value: the same non-zero subsidy for halvings 0 to
34 and 0 for halvings 35 to 63. The measured run above found no difference
below halving 64 and 35 differences from 64 to 98.

The change only replaces undefined results at heights 13,440,000 to 20,999,999
with 0, which matches the written intent ("Force block reward to zero when
right shift is undefined") and Bitcoin Core.

## Decision needed

This is still a consensus rule. Before any change:

1. The maintainers confirm the intended supply: zero subsidy from halving 35.
2. Decide whether it ships in an ordinary release (no block is affected for
   about 255 years) or waits for a future planned consensus change.
3. Add a unit test that checks `GetBlockSubsidy` at every halving boundary from
   0 to 200 against an independent calculation, and that the sum of subsidies
   never exceeds the stated supply ceiling.
4. Run that test under UndefinedBehaviorSanitizer on x86-64 and arm64.

Not measured: x86-64 behaviour, GCC, MSVC, and the behaviour of released Whive
binaries.
