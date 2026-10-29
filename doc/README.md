Whive Core
=============

Setup
---------------------
Whive Core is the original Whive client and it builds the backbone of the network. It downloads and, by default, stores the entire history of Whive transactions. Disk use and synchronization time have not been measured for this release. After syncing, `whive-cli getblockchaininfo` reports the space used as `size_on_disk`; starting with `-prune=<MiB>` reduces it.

Use 22.2.2 or later: older releases enforce a different block subsidy (see [release-notes-22.2.2.md](release-notes/release-notes-22.2.2.md)).

To download Whive Core, visit [whive.io](https://whive.io/) or the [releases page](https://github.com/whiveio/whive/releases).

To mine, start with the [mining quick-start](mining.md).

Running
---------------------
The following are some helpful notes on how to run Whive Core on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/whive-qt` (GUI) or
- `bin/whived` (headless)

### Windows

Unpack the files into a directory, and then run whive-qt.exe.

### macOS

Drag Whive Core to your applications folder, and then run Whive Core.

### Need Help?

* Read the [mining quick-start](mining.md) and the rest of this documentation.
* Report bugs on the [Whive Core issue tracker](https://github.com/whiveio/whive/issues). Do not post security problems there; see [SECURITY.md](/SECURITY.md).
* Ask the community on [Telegram](https://t.me/whiveio).
* Visit [whive.io](https://whive.io/).

Building
---------------------
The following are developer notes on how to build Whive Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)
- [Android Build Notes](build-android.md)
- [Gitian Building Guide (upstream Bitcoin Core, external link)](https://github.com/bitcoin-core/docs/blob/master/gitian-building.md)

Development
---------------------
The Whive repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Productivity Notes](productivity.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (upstream Bitcoin Core, external link)](https://doxygen.bitcoincore.org/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [JSON-RPC Interface](JSON-RPC-interface.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss Whive Core development in [issues and pull requests](https://github.com/whiveio/whive/issues).
* Whive improvement proposals live in the [WIP repository](https://github.com/whiveio/wips).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [whive.conf Configuration File](whive-conf.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [I2P Support](i2p.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [PSBT support](psbt.md)
- [Reduce Memory](reduce-memory.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
