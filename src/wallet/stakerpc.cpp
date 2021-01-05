#include <amount.h>
#include <chain.h>
#include <consensus/validation.h>
#include <core_io.h>
#include <httpserver.h>
#include <validation.h>
#include <key_io.h>
#include <net.h>
#include <outputtype.h>
#include <policy/feerate.h>
#include <policy/fees.h>
#include <policy/policy.h>
#include <policy/rbf.h>
#include <rpc/mining.h>
#include <rpc/rawtransaction.h>
#include <rpc/server.h>
#include <rpc/util.h>
#include <script/sign.h>
#include <shutdown.h>
#include <timedata.h>
#include <util.h>
#include <utilmoneystr.h>
#include <wallet/coincontrol.h>
#include <wallet/feebumper.h>
#include <wallet/rpcwallet.h>
#include <wallet/wallet.h>
#include <wallet/walletdb.h>
#include <wallet/walletutil.h>

#include <stdint.h>

#include <univalue/include/univalue.h>
//#include <univalue.h>

#include <functional>

static void ReleaseWallet(CWallet* wallet);

const fs::path& path = "/Desktop/whive-active";
int nMinDepth;


//std::auto_ptr<std::string> strAccount(new std::string("Lwanda"));

const std::string * strAccount;


 //std::shared_ptr<CWallet> lwallet = new CWallet("wallet.dat", WalletDatabase::Create(path))

std::shared_ptr<CWallet> walletLwanda(new CWallet("wallet.dat", WalletDatabase::Create(path)), ReleaseWallet);

CAmount Lwanda3 = walletLwanda->GetLegacyBalance(ISMINE_SPENDABLE, nMinDepth, strAccount);

 double LwandaX =   Lwanda3 / 100000000;

static void ReleaseWallet(CWallet* wallet)
{
    wallet->WalletLogPrintf("Releasing wallet\n");
    wallet->BlockUntilSyncedToCurrentChain();
    wallet->Flush();
    delete wallet;
}
