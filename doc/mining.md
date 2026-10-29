Mining quick-start
==================

This page takes you from nothing to a CPU miner working against your own Whive
node. It covers solo mining on mainnet. Hash rates and earnings have not been
measured for any hardware, so this page makes no claims about either.

1. Run a node
-------------

Use Whive Core **22.2.2 or later**. Older releases enforce a different block
subsidy and mine blocks that current nodes reject (see
[release-notes-22.2.2.md](release-notes/release-notes-22.2.2.md)).

Release 22.2.2 sends your IP address to ip-api.com over plain HTTP when it
starts. To avoid that, build from source that no longer contains
`src/crypto/yespower/optimizer.c` (see the [build notes](README.md#building)).

Create `whive.conf` in the data directory (see [whive-conf.md](whive-conf.md)
for its location) and make it readable only by you:

```ini
server=1
rpcbind=127.0.0.1
rpcallowip=127.0.0.1
rpcuser=choose-a-user
rpcpassword=choose-a-long-random-password
```

Keep RPC bound to `127.0.0.1`. The mainnet RPC port is `1867` and the peer
port is `8372`.

Start the node and wait for it to sync:

```bash
whived -daemon
whive-cli getblockchaininfo
```

The node is ready to mine when `initialblockdownload` is `false` and `blocks`
equals `headers`. You can use `whive-qt` instead of `whived`; run the same
commands in Window > Console without the `whive-cli` prefix.

2. Get a wallet address
-----------------------

```bash
whive-cli createwallet mining
whive-cli -rpcwallet=mining getnewaddress "" bech32
```

Mine to one of these mainnet address types:

- `wv1q...` — native SegWit v0, from `getnewaddress "" bech32`.
- `W...` — single-key P2PKH, from `getnewaddress "" legacy`.

Do not mine to Taproot (`wv1p...`), test-network addresses, or another coin's
address. Back up the wallet before you mine:

```bash
whive-cli -rpcwallet=mining backupwallet /path/to/backup/mining.dat
```

Never share the wallet file, seed or private keys.

3. Run the CPU miner
--------------------

Build [whive-cpuminer-mc-yespower](https://github.com/whiveio/whive-cpuminer-mc-yespower)
by following its README. Put the RPC credentials and your address in a file,
`whive-solo.json`, readable only by you (`chmod 600 whive-solo.json`), so they
stay out of your shell history:

```json
{
	"url" : "http://127.0.0.1:1867/",
	"user" : "choose-a-user",
	"pass" : "choose-a-long-random-password",
	"algo" : "yespower",
	"coinbase-addr" : "YOUR_WHIVE_ADDRESS"
}
```

Then start it:

```bash
./minerd -c whive-solo.json
```

Check that the address in the miner's output is the one you created. Some
miner builds do not check the address type for you.

4. Benchmark
------------

```bash
./minerd --benchmark -q
```

Benchmark mode hashes locally and connects to nothing. The figure it prints is
your local hash rate. It is not a forecast of blocks found or coins earned.
