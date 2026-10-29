# Security Policy

Whive Core is a fork of Bitcoin Core. Whive maintainers, not the Bitcoin Core
project, are responsible for Whive releases and for Whive-specific changes.
Do not send Whive vulnerability reports to Bitcoin Core.

## Supported Versions

| Version | Status |
|---------|--------|
| 22.2.2 | Latest release and minimum compatible version. It contains a location lookup that sends your IP address to ip-api.com over plain HTTP at startup; maintenance builds from source remove it. |
| Earlier than 22.2.2 | Not supported. These releases enforce a different block subsidy after block 210,000 (see [doc/release-notes/release-notes-22.2.2.md](doc/release-notes/release-notes-22.2.2.md)). |

## Reporting a Vulnerability

> **CONTACT PLACEHOLDER — not yet confirmed by the Whive maintainers.**
> A private reporting address and encryption key will be published here once
> the maintainers confirm who receives reports, how they are kept confidential
> and how reporters can verify the channel. Until then, there is no confirmed
> private channel.

While the placeholder stands:

- Do not post exploit details, proof-of-concept code or affected-node lists in
  public issues, pull requests or chat.
- Never send seeds, private keys, wallet files or passwords to anyone. No Whive
  maintainer will ask for them.
- If a problem also affects upstream Bitcoin Core, report that part to Bitcoin
  Core under its own security policy, and only the parts that apply to Bitcoin
  Core.

## What happens after a report

Once the contact is confirmed, the maintainers intend to acknowledge reports,
triage them, prepare and review a fix, publish recovery guidance where needed,
and coordinate disclosure with the reporter. No response time is promised until
the maintainers confirm they have capacity to meet it.
