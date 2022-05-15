// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <utilmoneystr.h>

#include <tinyformat.h>
//#include <utilstrencodings.h>
#include <util/strencodings.h>
#include <util/string.h>

std::string FormatMoney(const CAmount n)
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    static_assert(COIN > 1);
    int64_t quotient = n / COIN;
    int64_t remainder = n % COIN;
    if (n < 0) {
        quotient = -quotient;
        remainder = -remainder;
    }
    std::string str = strprintf("%d.%08d", quotient, remainder);

    // Right-trim excess zeros before the decimal point:
    int nTrim = 0;
    for (int i = str.size()-1; (str[i] == '0' && isdigit(str[i-2])); --i)
        ++nTrim;
    if (nTrim)
        str.erase(str.size()-nTrim, nTrim);

    if (n < 0)
        str.insert((unsigned int)0, 1, '-');
    return str;
}


bool ParseMoney(const std::string& money_string, CAmount& nRet)
{
    if (!ValidAsCString(money_string)) {
        return false;
    }
    const std::string str = TrimString(money_string);
    if (str.empty()) {
        return false;
    }

    std::string strWhole;
    int64_t nUnits = 0;
    const char* p = str.c_str();
    for (; *p; p++)
    {
        if (*p == '.')
        {
            p++;
            int64_t nMult = CENT*10;
            while (isdigit(*p) && (nMult > 0))
            {
                nUnits += nMult * (*p++ - '0');
                nMult /= 10;
            }
            break;
        }
        if (IsSpace(*p))
            return false;
        if (!IsDigit(*p))
            return false;
        strWhole.insert(strWhole.end(), *p);
    }
    if (*p) {
        return false;
    }
    if (strWhole.size() > 10) // guard against 63 bit overflow
        return false;
    if (nUnits < 0 || nUnits > COIN)
        return false;
    int64_t nWhole = atoi64(strWhole);
    CAmount nValue = nWhole*COIN + nUnits;

    nRet = nValue;
    return true;
}
