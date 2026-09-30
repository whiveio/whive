# Whive v29 integration readiness — developer review draft

> **Draft specification, not a release endorsement.** This branch contains the
> existing integration source plus review documentation. This proposal changes no
> consensus rule, activation parameter, hashing implementation or wallet format.

## Source base and relationship to other work

The review branch is `work/whive-v29-readiness-2027`, based exactly on
`origin/upgrade-to-bitcoin-v29` at
`fc45c09c637a37e322ad706f8bd03e68db4533e7`.

The separate maintenance review starts from
`889dcb01e69cdc8365da88c2f79cc9eb9254ae18`. Repairs and tests on that maintenance
base do not automatically certify this integration. Do not merge its entire
history merely to obtain a bounded correction. Evaluate each relevant patch
against this branch's actual callers, data structures and inherited behavior.

Shared specifications are being prepared in the [Whive WIP repository](https://github.com/whiveio/wips):
`drafts/consensus-preserving-core-maintenance.md`,
`drafts/yespower-compatibility.md`,
`drafts/wallet-interoperability-and-recovery.md`, and
`drafts/reproducible-releases-and-support.md`. Those drafts own shared
requirements; this document owns the branch-specific review. Their individual
pages are not asserted to be published or accepted. Operational progress remains
in the existing website task index; this is not a second status tracker.

## Reviewed source evidence

Every citation below is pinned to the integration base. These are source
observations, not executed compatibility or live activation measurements.

| Review area | Source observation and citation |
|---|---|
| Header synchronization | The [presync call](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/src/headerssync.cpp#L221) and [redownload call](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/src/headerssync.cpp#L267) select different difficulty-transition overloads. |
| Difficulty behavior | The [interval-based overload](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/src/pow.cpp#L83) and [chain-index-based overload](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/src/pow.cpp#L151) need a shared, native acceptance analysis. |
| Snapshot metadata | The [mainnet snapshot entry](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/src/kernel/chainparams.cpp#L192) requires independently derived provenance. The [field definition](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/src/kernel/chainparams.h#L53) states that transaction count is cumulative. |
| Native test assumptions | The [validation subsidy fixture](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/src/test/validation_tests.cpp#L24) must agree with the actual [subsidy implementation](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/src/validation.cpp#L1920). The [functional header helper](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/test/functional/test_framework/messages.py#L715) must represent native block identity where used. |
| Deployment state | [Mainnet Taproot configuration](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/src/kernel/chainparams.cpp#L114) describes parameters; it does not establish activation. The branch implements [getdeploymentinfo](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/src/rpc/blockchain.cpp#L1384) and [state reporting](https://github.com/whiveio/whive/blob/fc45c09c637a37e322ad706f8bd03e68db4533e7/src/rpc/blockchain.cpp#L1187). |

Reproduce a source observation with `git show <base>:<path>` using the exact
base above. Inspect the containing function and call sites, not only the linked
line. Record later changes against a new reviewed commit.

## Required invariants

Preserve existing genesis/network identity, successful block hashes, historical
proof-of-work parameter selection, difficulty arithmetic and compact-target
rounding, subsidy behavior, transaction validity and activation rules. Distinguish
consensus validation from header prevalidation, relay/mempool policy and wallet
behavior. Policy changes still need operator documentation and interoperability
tests even when they preserve block validity.

Do not alter start/timeout dates, activation heights, hash parameters, reward
rules or difficulty rules to make a failing integration test pass. An unexplained
reference/candidate discrepancy blocks release; it is not evidence that history
should be rewritten.

## Gate: historical replay and native fixtures

Select and build a pinned supported reference and this integration candidate in
separate data directories. Record the toolchains, actual executable names,
dependencies and source commits. Obtain an independently validated historical
corpus with network identity, observed tip, acquisition method and content
digests. The same explorer reached through a proxy is one source lineage.

Replay from genesis through the captured tip. Compare accepted block identities,
heights, chainwork and a consistently defined UTXO/state digest. If versions
expose different RPC or serialization forms, specify a common normalization
before comparing them. Include halving, difficulty and historical deployment
boundaries and controlled reorganizations. Do not use an assumed-valid or
snapshot shortcut as the only proof of historical validity.

Audit the actual compiled test set. Two similarly named source fixtures may
coexist, so a file's presence does not prove that its assertions execute. Trace
build registration and functional helper use, then fix inherited assumptions
using independently derived native vectors. Not every occurrence of a Bitcoin
amount in a generic test is a defect; change only an assumption that matters to
the tested behavior. Functional blocks must use native proof of work wherever
the node validates their identity.

**Acceptance evidence:** exact commands and build/test registration; reference
and candidate artifact digests; corpus provenance; accepted tip and common
state digest; boundary/reorg results; every mismatch classified and resolved.
Full replay and runtime test results are **not measured by this document**.

## Gate: header synchronization and difficulty consistency

Write down the intended native transition behavior before modifying the
overloads. Trace the header being checked, the previous index supplied, the
window of ancestors used and all minimum-difficulty/no-retarget cases. Review
whether each phase has enough authenticated context to make its check.

Verify presync, redownload and final block validation agree on legitimate
historical header sequences and reject invalid transitions at the appropriate
stage. Review presync calls into normal header processing, lock ownership,
already-indexed headers, state advancement, commitment accounting and bounded
memory. Preserve the synchronization design's resource limits; replacing a
cheap preliminary check with uncontrolled full processing is not automatically
safe or equivalent.

Test known and unknown headers, interruptions/restarts, peer changes, forks,
short history windows, malformed compact targets and boundary rounding. Include
mixed reference/candidate peers. Keep local computation/resource failure distinct
from peer-invalid input. No cache should turn an uncomputed hash into a durable
block identity or an invalid-peer result.

**Acceptance evidence:** a reviewed transition specification, native fixtures
shared across the phases, deterministic state-transition tests and executed
mixed-version synchronization. A source edit that makes both call sites use the
same overload is not sufficient proof.

## Gate: snapshot and acceleration-data provenance

Treat snapshot height, block hash, serialized UTXO hash and cumulative transaction
count as one linked record. Derive them from a fully validated chain using the
selected candidate's exact snapshot format, then reproduce through an independent
build/operator. Audit checkpoint, assumed-valid and chain-progress metadata by
the same provenance principle. Do not fill an unknown field with a plausible
number or mistake a per-block count for the cumulative value.

Until this evidence exists, propose disabling or excluding unverified snapshot
acceleration from the supported release path. That is a separate reviewed patch;
this documentation branch does not change it. Do not distribute a snapshot
merely because its hash appears in source. The existing [Assumeutxo guide](../assumeutxo.md)
is inherited guidance and must be adapted and exercised before advertising
native snapshot operations. Snapshot generation modes that alter temporary node
state belong on isolated nodes, not a user's operational wallet/node.

**Acceptance evidence:** matching independently derived metadata and artifacts,
successful background validation, mismatch/corruption rejection, interrupted-load
recovery, pruning/index interactions and explicit wallet-use limitations. An
ordinary full-sync path must remain available.

## Gate: activation measurement and capability documentation

Capture network, best block hash/height, node version and observation time before
querying deployment state. Use this candidate's `getdeploymentinfo` at a defined
tip or historical block as supported by the actual RPC interface, and compare
with independent chain-derived state or a compatible reference implementation.
Preserve evidence of current and next-block interpretation; a tip-state display
alone can be misread at a transition.

Do not infer activation from a configured historical window, version bit or
test-network behavior. Mainnet capability documentation must say “not measured”
until verified. Use only demonstrably active script capabilities in the first
agent-payment integration. If a desired capability is inactive, a new activation
proposal is outside this consensus-preserving release program.

**Acceptance evidence:** reproducible read-only queries tied to exact chain
observations, independently checked interpretation, tests at boundaries and
website/wallet documentation that agrees with the result. No RPC query against a
live node was executed for this document.

## Wallet, release and recovery dependencies

After the branch-specific gates, apply shared wallet interoperability and release
requirements. Use synthetic wallets to exercise descriptors, PSBT preparation,
signing separation and supported script policies. Test post-upgrade receiving,
change and restoration. Do not assume a migrated wallet can be reopened by an
older binary or that a pre-migration backup contains later receiving metadata.

Triage upstream maintenance changes individually and record the reason and
tests for each import. Publish a support matrix and reproducible candidate
artifacts only after review. The target event **2027-02-02T02:00:00Z** is a
release-planning objective, not an activation signal or compulsory network
upgrade. Unready features remain outside the verified release set.

## Contributor work and public disclosure

Useful bounded contributions are native fixtures, build-registration review,
historical replay, difficulty/header review, snapshot derivation, activation
measurement and migration rehearsal. Link actual commits, commands and observed
results; do not convert planned tests into success checkmarks. Respect existing
repository review and license requirements.

Keep sensitive reproductions and private operational details out of public
proposal commits. Use verified project reporting ownership before confidential
coordination; inherited upstream contact text is not proof of support for this
fork. This proposal contains public source references and acceptance requirements,
not credentials, private infrastructure or an incident-response guarantee.
