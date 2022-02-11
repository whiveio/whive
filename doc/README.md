Whive Core
=============

Setup
---------------------
Whive Core is the original Whive client and it builds the backbone of the network. It downloads and, by default, stores the entire history of Whive transactions, which requires a few hundred gigabytes of disk space. Depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download Whive Core, visit [whive.org](https://whive.io/).

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

* See the documentation at the [Whive Forum](https://forum.whive.org)
for help and more information.

Building
---------------------
The following are developer notes on how to build Whive Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Whive repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Productivity Notes](productivity.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/bitcoin/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [JSON-RPC Interface](JSON-RPC-interface.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [whive.conf Configuration File](whive-conf.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)
- [PSBT support](psbt.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
