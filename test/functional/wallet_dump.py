#!/usr/bin/env python3
# Copyright (c) 2016-2020 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test the dumpwallet RPC."""
import datetime
import os
import time

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import (
    assert_equal,
    assert_raises_rpc_error,
)


def read_dump(file_name, addrs, script_addrs, hd_master_addr_old):
    """
    Read the given dump, count the addrs that match, count change and reserve.
    Also check that the old hd_master is inactive
    """
    with open(file_name, encoding='utf8') as inputfile:
        found_comments = []
        found_legacy_addr = 0
        found_p2sh_segwit_addr = 0
        found_bech32_addr = 0
        found_script_addr = 0
        found_addr_chg = 0
        found_addr_rsv = 0
        witness_addr_ret = None
        hd_master_addr_ret = None
        for line in inputfile:
            line = line.strip()
            if not line:
                continue
            if line[0] == '#':
                found_comments.append(line)
            else:
                # split out some data
                key_date_label, comment = line.split("#")
                key_date_label = key_date_label.split(" ")
                # key = key_date_label[0]
                date = key_date_label[1]
                keytype = key_date_label[2]
                if not len(comment) or date.startswith('1970'):
                    continue

                addr_keypath = comment.split(" addr=")[1]
                addr = addr_keypath.split(" ")[0]
                keypath = None
                if keytype == "inactivehdseed=1":
                    # ensure the old master is still available
                    assert (hd_master_addr_old == addr)
                elif keytype == "hdseed=1":
                    # ensure we have generated a new hd master key
                    assert (hd_master_addr_old != addr)
                    hd_master_addr_ret = addr
                elif keytype == "script=1":
                    # scripts don't have keypaths
                    keypath = None
                else:
                    keypath = addr_keypath.rstrip().split("hdkeypath=")[1]

                # count key types
                for addrObj in addrs:
                    if addrObj['address'] == addr.split(",")[0] and addrObj['hdkeypath'] == keypath and keytype == "label=":
                        # a labeled entry in the wallet should contain both a native address
                        # and the p2sh-p2wpkh address that was added at wallet setup
                        if len(addr.split(",")) == 2:
                            addr_list = addr.split(",")
                            # the entry should be of the first key in the wallet
                            assert_equal(addrs[0]['address'], addr_list[0])
                            witness_addr_ret = addr_list[1]
                        found_addr += 1
                        break
                    elif keytype == "change=1":
                        found_addr_chg += 1
                        break
                    elif keytype == "reserve=1":
                        found_addr_rsv += 1
                        break

                # count scripts
                for script_addr in script_addrs:
                    if script_addr == addr.rstrip() and keytype == "script=1":
                        found_script_addr += 1
                        break

        return found_comments, found_legacy_addr, found_p2sh_segwit_addr, found_bech32_addr, found_script_addr, found_addr_chg, found_addr_rsv, hd_master_addr_ret


class WalletDumpTest(BitcoinTestFramework):
    def set_test_params(self):
        self.num_nodes = 1
        self.extra_args = [["-keypool=90", "-addresstype=legacy", "-deprecatedrpc=addwitnessaddress"]]
        self.rpc_timeout = 120

    def skip_test_if_missing_module(self):
        self.skip_if_no_wallet()

    def setup_network(self, split=False):
        self.add_nodes(self.num_nodes, extra_args=self.extra_args)
        self.start_nodes()

    def run_test(self):
        self.nodes[0].createwallet("dump")

        wallet_unenc_dump = os.path.join(self.nodes[0].datadir, "wallet.unencrypted.dump")
        wallet_enc_dump = os.path.join(self.nodes[0].datadir, "wallet.encrypted.dump")

        # generate 20 addresses to compare against the dump
        # but since we add a p2sh-p2wpkh address for the first pubkey in the
        # wallet, we will expect 21 addresses in the dump
        test_addr_count = 20
        addrs = []
        for address_type in ['legacy', 'p2sh-segwit', 'bech32']:
            for _ in range(test_addr_count):
                addr = self.nodes[0].getnewaddress(address_type=address_type)
                vaddr = self.nodes[0].getaddressinfo(addr)  # required to get hd keypath
                addrs.append(vaddr)

        # Test scripts dump by adding a 1-of-1 multisig address
        multisig_addr = self.nodes[0].addmultisigaddress(1, [addrs[1]["address"]])["address"]

        # Refill the keypool. getnewaddress() refills the keypool *before* taking a key from
        # the keypool, so the final call to getnewaddress leaves the keypool with one key below
        # its capacity
        self.nodes[0].keypoolrefill()

        self.log.info('Mine a block one second before the wallet is dumped')
        dump_time = int(time.time())
        self.nodes[0].setmocktime(dump_time - 1)
        self.nodes[0].generate(1)
        self.nodes[0].setmocktime(dump_time)
        dump_time_str = '# * Created on {}Z'.format(
            datetime.datetime.fromtimestamp(
                dump_time,
                tz=datetime.timezone.utc,
            ).replace(tzinfo=None).isoformat())
        dump_best_block_1 = '# * Best block at time of backup was {} ({}),'.format(
            self.nodes[0].getblockcount(),
            self.nodes[0].getbestblockhash(),
        )
        dump_best_block_2 = '#   mined on {}Z'.format(
            datetime.datetime.fromtimestamp(
                dump_time - 1,
                tz=datetime.timezone.utc,
            ).replace(tzinfo=None).isoformat())

        self.log.info('Dump unencrypted wallet')
        result = self.nodes[0].dumpwallet(wallet_unenc_dump)
        assert_equal(result['filename'], wallet_unenc_dump)

        found_comments, found_legacy_addr, found_p2sh_segwit_addr, found_bech32_addr, found_script_addr, found_addr_chg, found_addr_rsv, hd_master_addr_unenc = \
            read_dump(wallet_unenc_dump, addrs, [multisig_addr], None)
        assert '# End of dump' in found_comments  # Check that file is not corrupt
        assert_equal(dump_time_str, next(c for c in found_comments if c.startswith('# * Created on')))
        assert_equal(dump_best_block_1, next(c for c in found_comments if c.startswith('# * Best block')))
        assert_equal(dump_best_block_2, next(c for c in found_comments if c.startswith('#   mined on')))
        assert_equal(found_legacy_addr, test_addr_count)  # all keys must be in the dump
        assert_equal(found_p2sh_segwit_addr, test_addr_count)  # all keys must be in the dump
        assert_equal(found_bech32_addr, test_addr_count)  # all keys must be in the dump
        assert_equal(found_script_addr, 1)  # all scripts must be in the dump
        assert_equal(found_addr_chg, 0)  # 0 blocks where mined
        assert_equal(found_addr_rsv, 90 * 2)  # 90 keys plus 100% internal keys
        assert_equal(witness_addr_ret, witness_addr)  # p2sh-p2wsh address added to the first key

        # encrypt wallet, restart, unlock and dump
        self.nodes[0].encryptwallet('test')
        self.nodes[0].walletpassphrase('test', 100)
        # Should be a no-op:
        self.nodes[0].keypoolrefill()
        self.nodes[0].dumpwallet(wallet_enc_dump)

        found_comments, found_legacy_addr, found_p2sh_segwit_addr, found_bech32_addr, found_script_addr, found_addr_chg, found_addr_rsv, _ = \
            read_dump(wallet_enc_dump, addrs, [multisig_addr], hd_master_addr_unenc)
        assert '# End of dump' in found_comments  # Check that file is not corrupt
        assert_equal(dump_time_str, next(c for c in found_comments if c.startswith('# * Created on')))
        assert_equal(dump_best_block_1, next(c for c in found_comments if c.startswith('# * Best block')))
        assert_equal(dump_best_block_2, next(c for c in found_comments if c.startswith('#   mined on')))
        assert_equal(found_legacy_addr, test_addr_count)  # all keys must be in the dump
        assert_equal(found_p2sh_segwit_addr, test_addr_count)  # all keys must be in the dump
        assert_equal(found_bech32_addr, test_addr_count)  # all keys must be in the dump
        assert_equal(found_script_addr, 1)
        assert_equal(found_addr_chg, 90 * 2)  # old reserve keys are marked as change now
        assert_equal(found_addr_rsv, 90 * 2)
        assert_equal(witness_addr_ret, witness_addr)

        # Overwriting should fail
        assert_raises_rpc_error(-8, "already exists", lambda: self.nodes[0].dumpwallet(wallet_enc_dump))

        # Restart node with new wallet, and test importwallet
        self.restart_node(0)
        self.nodes[0].createwallet("w2")

        # Make sure the address is not IsMine before import
        result = self.nodes[0].getaddressinfo(multisig_addr)
        assert(result['ismine'] == False)

        self.nodes[0].importwallet(wallet_unenc_dump)

        # Now check IsMine is true
        result = self.nodes[0].getaddressinfo(multisig_addr)
        assert(result['ismine'] == True)

        self.log.info('Check that wallet is flushed')
        with self.nodes[0].assert_debug_log(['Flushing wallet.dat'], timeout=20):
            self.nodes[0].getnewaddress()

        # Make sure that dumpwallet doesn't have a lock order issue when there is an unconfirmed tx and it is reloaded
        # See https://github.com/bitcoin/bitcoin/issues/22489
        self.nodes[0].createwallet("w3")
        w3 = self.nodes[0].get_wallet_rpc("w3")
        w3.importprivkey(privkey=self.nodes[0].get_deterministic_priv_key().key, label="coinbase_import")
        w3.sendtoaddress(w3.getnewaddress(), 10)
        w3.unloadwallet()
        self.nodes[0].loadwallet("w3")
        w3.dumpwallet(os.path.join(self.nodes[0].datadir, "w3.dump"))

if __name__ == '__main__':
    WalletDumpTest().main()
