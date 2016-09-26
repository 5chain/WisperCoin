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

    static const size_t MIN_CREATE_NEW_COIN_COST = 10000 * COIN;

    static const string publicReceiptAddress("mwgB4hAhMPzE4i2omvC5kCb6HGoeFT5GCu");

    enum TxOutType
    {
        TXOUT_NORMAL = 0,
        TXOUT_CHANGE = 1,
        TXOUT_FEE = 2,
        TXOUT_NEW_COIN = 3,
        TXOUT_MAX = 4
    };

    static bool isCoinTypeValid(const string& coinType)
    {
        return ((coinType.size() >= MIN_COIN_TYPE_LENGTH) && (coinType.size() <= MAX_COIN_TYPE_LENGTH));
    }

    static bool isSentToPublicReceipt(const CScript &destScript)
    {
        CTxDestination address;
        if (!ExtractDestination(destScript, address))
            return false;

        return (address == CBitcoinAddress(publicReceiptAddress).Get());
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
    static const string allCoinTypeStr = MultiCoinType("*").ToString();

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

        bool tryGetNewCoinType(string& newCoinType) const
        {
            if (this->isCreateNewCoin())
            {
                newCoinType = mSecondType;

                return true;
            }

            return false;
        }

        // NOTE: Must have one main coin type.
        // Conditions are as follows: (X is currently only main coin type)
        //  X  -> tx.vout[ X |   X   | X-chg | X-fee ]  ...currently only for main coin
        // X|Y -> tx.vout[ X | X-chg | X-fee | Y-new ]  ...for create new coin
        // Y|X -> tx.vout[ Y | Y-chg | X-fee | X-chg ]  ...for new coin transaction
        bool isFitCoinType(const string &specifiedType, TxOutType txOutType) const
        {
            if (txOutType >= TXOUT_MAX)
                throw logic_error("isFitCoinType: wrong txout type.");

            // Currently only support main coin type exist alone.
            if (mSecondType.empty())
            {
                return (specifiedType == mFirstType);
            }
            else
            {
                if (mainCoinTypeStr == mFirstType)
                {
                    if (specifiedType == mFirstType)
                    {
                        return (txOutType != TXOUT_NEW_COIN);
                    }
                    else if (specifiedType == mSecondType)
                    {
                        return (txOutType == TXOUT_NEW_COIN);
                    }
                }
                else if (mainCoinTypeStr == mSecondType)
                {
                    if (specifiedType == mFirstType)
                    {
                        return (txOutType != TXOUT_FEE);
                    }
                    else if (specifiedType == mSecondType)
                    {
                        return (txOutType == TXOUT_FEE);
                    }
                }
            }

            return false;
        }

        bool isMainCoinTx() const
        {
            return (mFirstType == MultiCoins::mainCoinTypeStr) && mSecondType.empty();
        }

        // NOTE: for create new, this returns the main coin type
        string getSpendCoinType() const
        {
            return mFirstType;
        }

    private:
        string mFirstType;
        string mSecondType;
    };

    static const int64_t createNewCoinFee = 10 * COIN;
    static const float feeRatio = 1.f / 10000.f;

    // Be careful setting this: if you set it to zero then
    // a transaction spammer can cheaply fill blocks using
    // 1-satoshi-fee transactions. It should be set above the real
    // cost to you of processing a transaction.
    static const int64_t MIN_FEE = 0.1 * CENT;
    static const int64_t MAX_FEE = std::numeric_limits<int64_t>::max();

    // NOTE: the fee can be paied only by main coin type
    extern int64_t calculateTxFee(const CTransaction& tx);
    extern int64_t calculateTxFee(const string &coinTypeStr, int64_t txValue);
    extern int64_t getFeeInTx(const CTransaction& tx);

    static bool isFeeValid(int64_t amount)
    {
        return (amount >= MIN_FEE) && (amount <= MAX_FEE);
    }
};

#endif //SRC_MULTICOINS_H
