
DOWNLOAD
========

* Whive [WHIVE] Source code on github https://github.com/whiveio/whive


Useful links
============

* Website:        http://whive.io/

* Twitter:        https://twitter.com/whiveio
* Telegram   :    http://t.me/whiveio


Whive Core integration/staging tree
=====================================

What is Whive?
----------------

Whive, is a blockchain protocol that extends the Bitcoin Blockchain through enabling Trustless Rewards for Engineering Sustainable Solutions. Building on the success of Bitcoin the World's most secure blockchain, the Whive community has set out to build a cryptographically secure blockchain protocol and Auxiliary Chain(AuxChain) that will allow for building applications that trustlessly reward sustainable solutions.

To Build & Run
---------------------

```bash
./autogen.sh
./configure 
make
make install # optional
```

This will build whive-qt as well, if the dependencies are met.

Building
---------------------
The following are developer notes on how to build Whive Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](doc/dependencies.md)
- [macOS Build Notes](doc/build-osx.md)
- [Unix Build Notes](doc/build-unix.md)
- [Windows Build Notes](doc/build-windows.md)
- [OpenBSD Build Notes](doc/build-openbsd.md)
- [NetBSD Build Notes](doc/build-netbsd.md)
- [Gitian Building Guide](doc/gitian-building.md)

# `whive.conf` Configuration File

The configuration file is used by `whived`, `whive-qt` and `whive-cli`.

All command-line options (except for `-?`, `-help`, `-version` and `-conf`) may be specified in a configuration file, and all configuration file options (except for `includeconf`) may also be specified on the command line. Command-line options override values set in the configuration file and configuration file options override values set in the GUI.
The whive.conf file configurations:
```bash
server=1
daemon=1
listen=1
rpcuser=whive
rpcpassword=pass
```

## Configuration File Path

The configuration file is not automatically created; you can create it using your favorite text editor. By default, the configuration file name is `whive.conf` and it is located in the Whive data directory, but both the Whive data directory and the configuration file path may be changed using the `-datadir` and `-conf` command-line options.

The `includeconf=<file>` option in the `whive.conf` file can be used to include additional configuration files.

### Default configuration file locations

Operating System | Data Directory | Example Path
-- | -- | --
Windows | `%APPDATA%\Whive\` | `C:\Users\username\AppData\Roaming\Whive\whive.conf`
Linux | `$HOME/.whive/` | `/home/username/.whive/whive.conf`
macOS | `$HOME/Library/Application Support/Whive/` | `/Users/username/Library/Application Support/Whive/whive.conf`

You can find an example whive.conf file in [share/examples/whive.conf](../share/examples/whive.conf).

License
-------

Whive Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/whiveio/whive/tags) are created
regularly to indicate new official, stable release versions of The Whive Core.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.


