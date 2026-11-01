Whive Core 22.2.2 compatibility notes
=====================================

These notes were written on 2026-10-29 from the source history. Release 22.2.2
(tag `22.2.2`, commit `56ccfb28c7b796506ae371c6abff7c9a729ea067`, 2024-02-27)
shipped without a note describing its consensus change.

Block subsidy halving interval
------------------------------

From launch (`89fe94d81bb542ddd7b3f13ef5be682ed5162c21`, 2020-02-02) the block
subsidy halved every 1,000,000 blocks. Release 22.2.2 changed the halving
interval to 210,000 blocks on mainnet and testnet
(`consensus.nSubsidyHalvingInterval` in `src/chainparams.cpp`). Signet already
used 210,000 and regtest uses 150; neither changed.

The subsidy still starts at 200 WHIVE per block. Under the 22.2.2 rules it is
100 WHIVE from block 210,000, 50 WHIVE from block 420,000, and so on.

Minimum compatible version
--------------------------

**22.2.2 is the minimum compatible version.** Releases before 22.2.2 allow a
200 WHIVE subsidy for blocks 210,000 to 999,999, where current rules allow
100 WHIVE:

- A miner using an older release creates blocks that pay too much. Nodes running
  22.2.2 or later reject them (`bad-cb-amount`).
- An older node accepts those blocks, so it can end up on a different chain from
  current nodes.

Upgrade any node or miner older than 22.2.2.

Known issue in 22.2.2
---------------------

Release 22.2.2 contains a location lookup (`optimizer()` in
`src/crypto/yespower/optimizer.c`). At startup, and in each new hashing thread,
it sends a plain HTTP request to ip-api.com on port 80, which reveals the
node's IP address to that service. It parses the unauthenticated reply without
bounds checks, and the result is not used. `master` still contains it. Until
it is merged, only the maintenance branch
`work/whive-22.2.2-maintenance-candidate-2026-10-29` (commit `d67c152882`)
removes it. No release without it has been published yet.
