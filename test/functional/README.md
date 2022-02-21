# Functional tests

### Writing Functional Tests

#### Example test

The file [test/functional/example_test.py](example_test.py) is a heavily commented example
of a test case that uses both the RPC and P2P interfaces. If you are writing your first test, copy
that file and modify to fit your needs.

#### Coverage

Running `test/functional/test_runner.py` with the `--coverage` argument tracks which RPCs are
called by the tests and prints a report of uncovered RPCs in the summary. This
can be used (along with the `--extended` argument) to find out which RPCs we
don't have test cases for.

#### Style guidelines

- Where possible, try to adhere to [PEP-8 guidelines](https://www.python.org/dev/peps/pep-0008/)
- Use a python linter like flake8 before submitting PRs to catch common style
  nits (eg trailing whitespace, unused imports, etc)
- See [the python lint script](/test/lint/lint-python.sh) that checks for violations that
  could lead to bugs and issues in the test code.
- Avoid wildcard imports where possible
- Use a module-level docstring to describe what the test is testing, and how it
  is testing it.
- When subclassing the BitcoinTestFramwork, place overrides for the
  `set_test_params()`, `add_options()` and `setup_xxxx()` methods at the top of
  the subclass, then locally-defined helper methods, then the `run_test()` method.
- Use `'{}'.format(x)` for string formatting, not `'%s' % x`.

#### Naming guidelines

- Name the test `<area>_test.py`, where area can be one of the following:
    - `feature` for tests for full features that aren't wallet/mining/mempool, eg `feature_rbf.py`
    - `interface` for tests for other interfaces (REST, ZMQ, etc), eg `interface_rest.py`
    - `mempool` for tests for mempool behaviour, eg `mempool_reorg.py`
    - `mining` for tests for mining features, eg `mining_prioritisetransaction.py`
    - `p2p` for tests that explicitly test the p2p interface, eg `p2p_disconnect_ban.py`
    - `rpc` for tests for individual RPC methods or features, eg `rpc_listtransactions.py`
    - `wallet` for tests for wallet features, eg `wallet_keypool.py`
- use an underscore to separate words
    - exception: for tests for specific RPCs or command line options which don't include underscores, name the test after the exact RPC or argument name, eg `rpc_decodescript.py`, not `rpc_decode_script.py`
- Don't use the redundant word `test` in the name, eg `interface_zmq.py`, not `interface_zmq_test.py`

#### General test-writing advice

- Instead of inline comments or no test documentation at all, log the comments to the test log, e.g.
  `self.log.info('Create enough transactions to fill a block')`. Logs make the test code easier to read and the test
  logic easier [to debug](/test/README.md#test-logging).
- Set `self.num_nodes` to the minimum number of nodes necessary for the test.
  Having additional unrequired nodes adds to the execution time of the test as
  well as memory/CPU/disk requirements (which is important when running tests in
  parallel).
- Avoid stop-starting the nodes multiple times during the test if possible. A
  stop-start takes several seconds, so doing it several times blows up the
  runtime of the test.
- Set the `self.setup_clean_chain` variable in `set_test_params()` to control whether
  or not to use the cached data directories. The cached data directories
  contain a 200-block pre-mined blockchain and wallets for four nodes. Each node
  has 25 mature blocks (25x50=1250 BTC) in its wallet.
- When calling RPCs with lots of arguments, consider using named keyword
  arguments instead of positional arguments to make the intent of the call
  clear to readers.

#### RPC and P2P definitions

Test writers may find it helpful to refer to the definitions for the RPC and
P2P messages. These can be found in the following source files:

- `/src/rpc/*` for RPCs
- `/src/wallet/rpc*` for wallet RPCs
- `ProcessMessage()` in `/src/net_processing.cpp` for parsing P2P messages

#### Using the P2P interface

- [messages.py](test_framework/messages.py) contains all the definitions for objects that pass
over the network (`CBlock`, `CTransaction`, etc, along with the network-level
wrappers for them, `msg_block`, `msg_tx`, etc).

- P2P tests have two threads. One thread handles all network communication
with the whived(s) being tested in a callback-based event loop; the other
implements the test logic.

- `P2PConnection` is the class used to connect to a whived.  `P2PInterface`
contains the higher level logic for processing P2P payloads and connecting to
the Whive Core node application logic. For custom behaviour, subclass the
P2PInterface object and override the callback methods.

- Can be used to write tests where specific P2P protocol behavior is tested.
Examples tests are [p2p_unrequested_blocks.py](p2p_unrequested_blocks.py),
[p2p_compactblocks.py](p2p_compactblocks.py).

#### Prototyping tests

The [`TestShell`](test-shell.md) class exposes the BitcoinTestFramework
functionality to interactive Python3 environments and can be used to prototype
tests. This may be especially useful in a REPL environment with session logging
utilities, such as
[IPython](https://ipython.readthedocs.io/en/stable/interactive/reference.html#session-logging-and-restoring).
The logs of such interactive sessions can later be adapted into permanent test
cases.

### Test framework modules
The following are useful modules for test developers. They are located in
[test/functional/test_framework/](test_framework).

#### [authproxy.py](test_framework/authproxy.py)
Taken from the [python-bitcoinrpc repository](https://github.com/jgarzik/python-bitcoinrpc).

#### [test_framework.py](test_framework/test_framework.py)
Base class for functional tests.

#### [util.py](test_framework/util.py)
Generally useful functions.

#### [mininode.py](test_framework/mininode.py)
Basic code to support P2P connectivity to a bitcoind.

#### [script.py](test_framework/script.py)
Utilities for manipulating transaction scripts (originally from python-bitcoinlib)

#### [key.py](test_framework/key.py)
Test-only secp256k1 elliptic curve implementation

#### [blocktools.py](test_framework/blocktools.py)
Helper functions for creating blocks and transactions.
