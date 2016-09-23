//
// Created by LiSuyong on 9/22/16.
//

#ifndef SRC_MULTICOINS_H
#define SRC_MULTICOINS_H

#include "base58.h"
#include "chainparams.h"

#include <boost/algorithm/string.hpp>

using namespace std;

namespace MultiCoins
{
    static const size_t MIN_COIN_TYPE_LENGTH = 3;
    static const size_t MAX_COIN_TYPE_LENGTH = 10;

    static const string publicReceiptAddress("mwgB4hAhMPzE4i2omvC5kCb6HGoeFT5GCu");

    static bool isCoinTypeValid(const string& coinType)
    {
        return ((coinType.size() >= MIN_COIN_TYPE_LENGTH) && (coinType.size() <= MAX_COIN_TYPE_LENGTH));
    }

    static bool isReceiptAddressValid(CTxDestination& destAddress)
    {
        return (destAddress == CBitcoinAddress(publicReceiptAddress).Get());
    }

    class MultiCoinType //: public CBase58Data
    {
    public:
        MultiCoinType(const std::string& originTypeStr = string())
        {
            mType = originTypeStr;
            //SetData(Params().Base58Prefix(CChainParams::COIN_TYPE), originTypeStr.c_str(), originTypeStr.size());
        }

        string decodeTypeStr()
        {
            //return (this->SetString(typeStr)) ? string(vchData.begin(), vchData.end()) : string();
            return mType;
        }

        string ToString()
        {
            return mType;
        }

    private:
        string mType;
    };

    static const string mainCoinTypeStr = MultiCoinType("wsc").ToString();

    class CoinType
    {
    public:
        explicit CoinType(const string& typeStr)
        {
            if (typeStr.find('|') == string::npos)
            {
                mFirstType = typeStr;

                if (!isCoinTypeValid(mFirstType))
                    throw logic_error("CoinType: construct error!");

                if (mFirstType != mainCoinTypeStr)
                    throw logic_error("CoinType: currently only support main coin type exist alone!");
            }
            else
            {
                vector<string> strVec;
                boost::split(strVec, typeStr, boost::is_any_of("|"));

                if (strVec.size() != 2)
                    throw logic_error("CoinType parse error!");

                mFirstType = strVec[0];
                mSecondType = strVec[1];

                if (!isCoinTypeValid(mFirstType) || !isCoinTypeValid(mSecondType))
                    throw logic_error("CoinType parse error!");
            }
        }

        bool isCreateNewCoin() const
        {
            if ((mFirstType == mainCoinTypeStr) && !mSecondType.empty())
                return true;

            return false;
        }

        bool getNewCoinType(string& newCoinType) const
        {
            if (this->isCreateNewCoin())
            {
                newCoinType = mSecondType;

                return true;
            }

            return false;
        }

        // NOTE: Must have one main coin type.
        // Conditions as follows:
        // X|Y -> tx.vout[ X | X | Y ]
        // Y|X -> tx.vout[ Y | Y | X ]
        //  X  -> tx.vout[ X | X | X ]  ...currently only main coin type suit this type.
        bool isFitCoinType(const string& specifiedType, unsigned int outVecIdx, unsigned int outVecSize) const
        {
            if (outVecIdx >= outVecSize)
                throw logic_error("isFitCoinType: param outVecIdx out of range.");

            // Currently only support main coin type exist alone.
            if (mSecondType.empty())
            {
                return (specifiedType == mFirstType);
            }
            else
            {
                if (specifiedType == mFirstType)
                {
                    return (outVecIdx <= outVecSize - 2);
                }
                else if (specifiedType == mSecondType)
                {
                    return (outVecIdx == outVecSize - 1);
                }
            }

            return false;
        }

    private:
        string mFirstType;
        string mSecondType;
    };

};

#endif //SRC_MULTICOINS_H
