# Whive Core modernization proposal

> **Draft for contributing developers.** Proposed acceptance requirements do not assert that implementation, testing, upstream acceptance or deployment has occurred.

## Source and scope

Reviewed repository base: `889dcb01e69cdc8365da88c2f79cc9eb9254ae18`. The local review branch is `work/whive-readiness-2027`. Software changes after that base require their own verification evidence; this document does not certify them.

Shared specification: `consensus-preserving-core-maintenance.md` in the [Whive WIP repository](https://github.com/whiveio/wips), under `drafts/`. That draft package is being prepared locally; its individual pages are not asserted to be published. The WIP specifies common invariants; this document describes this repository's implementation work. Operational status remains in the website task index.

## Motivation and compatibility invariants

Maintain a usable, supportable node and wallet while preserving the existing chain. The existing v29 integration at `fc45c09c637a37e322ad706f8bd03e68db4533e7` is an additional review base, not an accepted release. Preserve successful block hashes, difficulty/subsidy arithmetic, genesis/network identity, transaction validity and historical activation behavior. Do not describe a deployment as active merely because it appears in chain parameters.

Classify imports as consensus, policy, P2P, wallet, build or documentation changes. A patch described as a bug fix still needs semantic review. Keep uncertain changes, including future-height arithmetic behavior, outside a narrow maintenance release until independently analyzed.

## Implementation sequence

Inventory versions actually operated before choosing a maintenance backport. Compare the chosen maintenance and v29 bases; do not cherry-pick an entire integration commit to obtain one correction. Review `src/pow.cpp`, `src/headerssync.cpp` on the integration branch, chain parameters, block-hash callers and caches as one compatibility boundary.

Align both header synchronization phases with native difficulty checks. Replace inherited Bitcoin fixtures in `src/test/` and `test/functional/` with provenance-backed Whive fixtures. Inspect snapshot/checkpoint/assume-valid data using an independent chain-derived procedure; disable unverified acceleration data until checked. Document existing PSBT/descriptors/watch-only flows and relay-policy differences separately from consensus.

Update contributor routing in a focused documentation patch: this fork's patches and review belong in its actual repository. References to upstream GUI/node repositories and mailing channels must distinguish upstream work from Whive work. Propose a verified Whive security policy rather than assuming upstream contact ownership.

## Migration and recovery

Use separate experimental data directories. Document database/wallet-format transitions and any inability to reopen a migrated wallet with an old binary. Rehearse recovery after receiving and spending with the upgraded wallet, including newly generated change. A backup made before new receiving keys exist may not describe all later funds; explain the actual recovery material required.

## Acceptance tests to implement and run

Build both pinned reference and candidate with recorded toolchains. Run relevant native unit, functional and fuzz tests; compare historical header/block acceptance and state against the reference, including difficulty boundaries and reorgs. Exercise presync/redownload agreement, corrupted data and local-resource failure. Verify snapshot metadata from chain-derived counts before enabling snapshots.

Run controlled watch-only/unsigned-PSBT/sign/broadcast workflows and fee/replacement rejection paths. Record exact commands, source SHAs, accepted tips/state digests and failures. Inspect the real `test/functional/test_runner.py` options and current build documentation before writing a command into release instructions; tests proposed here are not claimed executed.

## Dependencies, alternatives and open questions

Requires shared Yespower and wallet fixtures plus release provenance. Actual deployed versions, live script activation, full replay results, operator capacity and supported platforms remain to be measured. Finishing the reviewed integration can be less work than chasing a new major version; a narrow maintenance release can precede it when real deployed users need it. Needed reviewers include consensus/difficulty, wallet recovery, build and networking specialists.

## Contribution and disclosure

Keep changes focused, preserve history and existing licenses, and provide exact source revision, command, observed outcome and run identifier. Human review applies equally to agent-authored patches. A successful documentation check does not prove runtime behavior. Do not publish sensitive security reproductions or private operations in this proposal. Verify the responsible reporting contact before confidential coordination; inherited upstream policies are not proof of Whive support.

External messages, remote publication, default-branch merges and production changes require their own authorized workflow. The target launch event does not override acceptance gates or voluntary operator adoption.
