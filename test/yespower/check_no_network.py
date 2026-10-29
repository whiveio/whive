#!/usr/bin/env python3
"""Static guard: consensus hashing must not contact the network or ignore errors.

Reads source text only. It compiles and runs nothing, so it is safe to run on
trees that still contain the removed optimizer.
"""
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/crypto/yespower"
NETWORK = re.compile(r"ip-api|getaddrinfo|\bsocket\s*\(|\bconnect\s*\(|\bsend\s*\(|\brecv\s*\(|curl_")


def main():
    failures = []
    for name in ("optimizer.c", "optimizer.h"):
        if (SOURCE / name).exists():
            failures.append(f"{name} is still present")
    for path in sorted(SOURCE.glob("*.[ch]")):
        text = path.read_text(errors="replace")
        for number, line in enumerate(text.splitlines(), 1):
            if NETWORK.search(line) or re.search(r"\b(optimizer|randomizer)\s*\(", line):
                failures.append(f"{path.relative_to(ROOT)}:{number}: {line.strip()}")
    if re.search(r"crypto/yespower/optimizer\.c", (ROOT / "src/Makefile.am").read_text()):
        failures.append("src/Makefile.am still builds crypto/yespower/optimizer.c")
    opt = (SOURCE / "yespower-opt.c").read_text()
    check = re.search(r"errno = EINVAL;\s*(.*?)\n", opt)
    if not check or check.group(1).strip() != "return -1;":
        failures.append("yespower-opt.c parameter check does not return -1 after EINVAL")
    for failure in failures:
        print("FAIL", failure)
    print(f"checked {len(list(SOURCE.glob('*.[ch]')))} files: {'FAIL' if failures else 'PASS'} ({len(failures)} problems)")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
