#!/usr/bin/env python3
"""Compile production C implementations and compare against independent fixtures.

No node, miner, network, wallet, or project dependency installation is involved.
"""
import argparse
import json
import os
from pathlib import Path
import shlex
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/crypto/yespower"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--sanitize", action="store_true")
    parser.add_argument("--sanitizers", default="address,undefined", choices=("address,undefined", "undefined"))
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    receipt = {"scope": "standalone production Yespower C code", "sanitizers": args.sanitizers if args.sanitize else None,
               "full_node_replay": "not measured", "commands": []}
    cc = shlex.split(os.environ.get("CC", "cc"))
    flags = ["-std=c99", "-O1" if args.sanitize else "-O2", "-pthread", "-I", str(SOURCE)]
    if args.sanitize:
        flags += ["-g", "-fsanitize=" + args.sanitizers, "-fno-sanitize-recover=all", "-fno-omit-frame-pointer"]
    outputs = {}
    with tempfile.TemporaryDirectory(prefix="whive-yespower-") as temp:
        for implementation in ("ref", "opt"):
            for suite in ("upstream", "headers"):
                binary = Path(temp) / f"{implementation}-{suite}"
                source = SOURCE / "tests.c" if suite == "upstream" else Path(__file__).with_name("driver.c")
                command = cc + flags + [str(source), str(SOURCE / f"yespower-{implementation}.c"),
                           str(SOURCE / "sha256.c"), str(SOURCE / "yespower.c"), "-o", str(binary)]
                subprocess.run(command, check=True)
                receipt["commands"].append(shlex.join(command))
                output = subprocess.check_output([str(binary)], text=True)
                receipt["commands"].append(str(binary))
                outputs[implementation, suite] = output
        expected = (SOURCE / "TESTS-OK").read_text()
        assert outputs["ref", "upstream"] == expected, "reference differs from checked-in known answers"
        assert outputs["opt", "upstream"] == expected, "optimized differs from checked-in known answers"
        assert outputs["ref", "headers"] == outputs["opt", "headers"], "header implementations disagree"
        headers = dict(line.split(" ", 1) for line in outputs["ref", "headers"].splitlines())
        metrics = json.loads(headers.pop("metrics"))
        assert headers["fixture"] == "d5efb813cd263e9b34540130233cbbc6a921fbff3431e5ec1a1abde2aea6ff4d"
        assert bytes.fromhex(headers["genesis"])[::-1].hex() == "00006142c9cae8009a078004c219fdb5d4a9116d8508e348d430c1be24e3d68a"
        assert bytes.fromhex(headers["regtest-genesis"])[::-1].hex() == "4068eeb97b5435fb3371de735b289d48a8edfa660c9c00197434de9da3f7097c"
        assert len({headers[key] for key in ("before", "boundary", "after")}) == 3
        receipt.update(result="PASS", known_answers=len(expected.splitlines()),
                       header_vectors=len(headers) - 1, **metrics)
    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(json.dumps(receipt, indent=2) + "\n")
    print(json.dumps({key: value for key, value in receipt.items() if key != "commands"}, indent=2))


if __name__ == "__main__":
    main()
