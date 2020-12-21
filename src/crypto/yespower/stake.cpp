/*by @lwandamagere
#include <wallet/wallet.h>

#include <checkpoints.h>
#include <chain.h>
#include <wallet/coincontrol.h>
#include <consensus/consensus.h>
#include <consensus/validation.h>
#include <fs.h>
#include <key.h>
#include <key_io.h>
#include <keystore.h>
#include <validation.h>
#include <net.h>
#include <policy/fees.h>
#include <policy/policy.h>
#include <policy/rbf.h>
#include <primitives/block.h>
#include <primitives/transaction.h>
#include <script/script.h>
#include <shutdown.h>
#include <timedata.h>
#include <txmempool.h>
#include <utilmoneystr.h>
#include <wallet/fees.h>
#include <wallet/walletutil.h>

#include <algorithm>
#include <assert.h>
#include <future>

#include <boost/algorithm/string/replace.hpp>

CWallet * Magere;

//extern const double Lwanda = Magere->GetAvailableBalance();

*/
#include <stdio.h>
#include <interfaces/wallet.cpp>

//Dado
std::shared_ptr<CWallet> hared_wallet;
std::shared_ptr<interfaces::WalletImpl> ps(new interfaces::WalletImpl(hared_wallet));
//extern int Lwanda = ps->getBalance();
int Lwanda = ps->getBalance();
printf("Lwanda: %d \n", Lwanda);
