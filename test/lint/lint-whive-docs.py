#!/usr/bin/env python3
#
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Check first-time user docs for Whive-specific contacts, links and claims.

Each check prints PASS or FAIL. Exit status is 1 if any check fails.
"""
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[2]
BITCOIN_SUPPORT = re.compile(r"bitcoincore\.org|bitcoin\.stackexchange|bitcointalk\.org|libera\.chat/#bitcoin|#bitcoin")


def read(name):
    path = ROOT / name
    return path.read_text(encoding="utf8") if path.exists() else ""


def checks():
    security = read("SECURITY.md")
    yield "SECURITY.md does not route reports to Bitcoin Core", security and "bitcoincore.org" not in security
    yield "SECURITY.md marks the contact as an unconfirmed placeholder", "CONTACT PLACEHOLDER" in security

    notes = read("doc/release-notes/release-notes-22.2.2.md")
    yield "22.2.2 notes record the halving change 1,000,000 -> 210,000", "1,000,000" in notes and "210,000" in notes
    yield "22.2.2 notes state 22.2.2 is the minimum compatible version", "minimum compatible version" in notes
    yield "doc/release-notes.md links the 22.2.2 compatibility notes", "release-notes-22.2.2.md" in read("doc/release-notes.md")

    windows = read("doc/README_windows.txt")
    yield "README_windows.txt has no broken forum/whive.org link", windows and "forum/whive.org" not in windows
    readme = read("doc/README.md")
    yield "doc/README.md has no Bitcoin support links", readme and not BITCOIN_SUPPORT.search(readme)
    yield "doc/README.md has no unmeasured 'few hundred gigabytes' claim", readme and "few hundred gigabytes" not in readme
    yield "doc/README.md links the mining quick-start", "mining.md" in readme

    mining = read("doc/mining.md")
    for term in ("whived", "getnewaddress", "wv1q", "W...", "minerd -c", "--benchmark"):
        yield f"doc/mining.md covers {term}", term in mining

    proposal = read("doc/proposals/subsidy-shift-guard.md")
    yield "subsidy shift proposal exists and is marked proposal-only", "Proposal only" in proposal


def main():
    failures = 0
    for name, ok in checks():
        print(("PASS " if ok else "FAIL ") + name)
        failures += not ok
    print(f"{failures} failing")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
