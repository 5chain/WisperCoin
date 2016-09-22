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
    // For the main coin called wsc.
    static const string mainCoinTypeStr = MultiCoinType("wsc").ToString();
    static const string publicReceiptAddress("");

    class MultiCoinType : public CBase58Data
    {
    public:
        MultiCoinType(const std::string& originTypeStr)
        {
            SetData(Params().Base58Prefix(CChainParams::COIN_TYPE), originTypeStr.c_str(), originTypeStr.size());
        }

        static string decodeTypeStr(const string& typeStr)
        {
            CBase58Data type;
            type.SetString(typeStr);

            return string(type.vchData.begin(), type.vchData.end());
        }
    };
};

#endif //SRC_MULTICOINS_H
