// Copyright (c) 2013-2019 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_NOUI_H
#define BITCOIN_NOUI_H

extern void noui_connect();

/** Redirect all bitcoind signal handlers to LogPrintf. Used to check or suppress output during test runs that produce expected errors */
void noui_test_redirect();

/** Reconnects the regular Non-GUI handlers after having used noui_test_redirect */
void noui_reconnect();

#endif // BITCOIN_NOUI_H
