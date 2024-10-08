#!/usr/bin/env python3
# Copyright (c) 2017-2020 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test deprecation of RPC calls."""
from test_framework.test_framework import BitcoinTestFramework

class DeprecatedRpcTest(BitcoinTestFramework):
    def set_test_params(self):
        self.num_nodes = 2
        self.setup_clean_chain = True
        self.extra_args = [[], ['-deprecatedrpc=bumpfee']]

    def run_test(self):
        # This test should be used to verify correct behaviour of deprecated
        # RPC methods with and without the -deprecatedrpc flags. For example:
        #
        # self.log.info("Make sure that -deprecatedrpc=createmultisig allows it to take addresses")
        # assert_raises_rpc_error(-5, "Invalid public key", self.nodes[0].createmultisig, 1, [self.nodes[0].getnewaddress()])
        # self.nodes[1].createmultisig(1, [self.nodes[1].getnewaddress()])

        self.log.info("Test validateaddress deprecation")
        SOME_ADDRESS = "mnvGjUy3NMj67yJ6gkK5o9e5RS33Z2Vqcu"  # This is just some random address to pass as a parameter to validateaddress
        dep_validate_address = self.nodes[0].validateaddress(SOME_ADDRESS)
        assert "ismine" not in dep_validate_address
        not_dep_val = self.nodes[1].validateaddress(SOME_ADDRESS)
        assert "ismine" in not_dep_val

        self.log.info("Test accounts deprecation")
        # The following account RPC methods are deprecated:
        # - getaccount
        # - getaccountaddress
        # - getaddressesbyaccount
        # - getreceivedbyaccount
        # - listaccouts
        # - listreceivedbyaccount
        # - move
        # - setaccount
        #
        # In run_test:
        # self.log.info("Test generate RPC")
        # assert_raises_rpc_error(-32, 'The wallet generate rpc method is deprecated', self.nodes[0].rpc.generate, 1)
        # self.nodes[1].generate(1)

        self.log.info("No tested deprecated RPC methods")

if __name__ == '__main__':
    DeprecatedRpcTest().main()
