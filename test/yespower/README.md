# Standalone header hashing checks

Run `python3 test/yespower/check.py`, then
`python3 test/yespower/check.py --sanitize` with a compiler supporting AddressSanitizer
and UndefinedBehaviorSanitizer. Use `--report /path/to/receipt.json` to save commands
and measured outcomes. Build products are temporary and removed after the run.
Use `--sanitize --sanitizers undefined` when only UndefinedBehaviorSanitizer is
available; do not describe that run as an AddressSanitizer check.

The checks compile the actual reference implementation, optimized implementation,
and header wrapper. They compare the existing known answers, mainnet and regtest
genesis identifiers, historical parameter-selection boundaries, synthetic headers,
invalid parameters, and concurrent calls. They do not run a node or miner.

These tests are a local compatibility gate, not evidence of a released binary or
complete chain replay. Full-node error propagation, persistent hash-cache handling,
historical replay, additional architectures, and mixed-version integration remain
separate release requirements. No subsidy, difficulty, activation, or wallet format
change is included in this maintenance work.
