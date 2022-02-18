// Copyright (c) 2013-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_NOUI_H
#define BITCOIN_NOUI_H

extern void noui_connect();

/** Suppress all bitcoind signal handlers. Used to suppress output during test runs that produce expected errors */
void noui_suppress();

/** Reconnects the regular Non-GUI handlers after having used noui_suppress */
void noui_reconnect();

#endif // BITCOIN_NOUI_H
