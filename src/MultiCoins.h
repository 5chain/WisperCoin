//
// Created by LiSuyong on 9/22/16.
//

#ifndef SRC_MULTICOINS_H
#define SRC_MULTICOINS_H

#include "base58.h"
#include "chainparams.h"

using namespace std;

namespace MultiCoins
{
    static const size_t MIN_COIN_NAME_LENGTH = 3;
    static const size_t MAX_COIN_NAME_LENGTH = 10;

    static const string publicReceiptAddress("mwgB4hAhMPzE4i2omvC5kCb6HGoeFT5GCu");

    static bool isCoinNameValid(const string& coinName)
    {
        return ((coinName.size() >= MIN_COIN_NAME_LENGTH) && (coinName.size() <= MAX_COIN_NAME_LENGTH));
    }

    static bool isReceiptAddressValid(CTxDestination& destAddress)
    {
        return (destAddress == CBitcoinAddress(publicReceiptAddress).Get());
    }

    class MultiCoinType : public CBase58Data
    {
    public:
        MultiCoinType(const std::string& originTypeStr = string())
        {
            SetData(Params().Base58Prefix(CChainParams::COIN_TYPE), originTypeStr.c_str(), originTypeStr.size());
        }

        string decodeTypeStr(const string& typeStr)
        {
            return (this->SetString(typeStr)) ? string(vchData.begin(), vchData.end()) : string();
        }
    };

    static const string mainCoinTypeStr = MultiCoinType("wsc").ToString();
};

#endif //SRC_MULTICOINS_H
