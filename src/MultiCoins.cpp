//
// Created by LiSuyong on 9/24/16.
//

#include "MultiCoins.h"
#include "txdb.h"
#include "main.h"

#include <boost/algorithm/clamp.hpp>
#include <boost/foreach.hpp>

namespace MultiCoins
{
    int64_t calculateTxFee(const CTransaction &tx)
    {
        if (tx.IsCoinBase() || tx.IsCoinStake())
            return 0;

        int64_t txValue = 0;

        if (!tx.isCreateNewCoin())
        {
            if (tx.isMainCoinTx())
            {
                BOOST_FOREACH(const CTxOut &txOut, tx.vout)
                {
                    if (txOut.getType() == TXOUT_NORMAL)
                        txValue += txOut.nValue;
                }
            }
            else // This is for new coin transactions.
            {
                BOOST_FOREACH(const CTxOut &txOut, tx.vout)
                {
                    if (txOut.getType() == TXOUT_NORMAL)
                        txValue += txOut.nValue;
                }
            }
        }

        return calculateTxFee(tx.getCoinTypeStr(), txValue);
    }

    int64_t calculateTxFee(const string &coinTypeStr, int64_t txValue)
    {
        int64_t feeVal = 0;
        CoinType coinType(coinTypeStr);

        if (coinType.isCreateNewCoin())
        {
            feeVal = createNewCoinFee;
        }
        else if (coinType.isMainCoinTx())
        {
            feeVal = txValue * feeRatio;
        }
        else // This is for new coin transactions.
        {
            int64_t newCoinFee = txValue * feeRatio;

            // Then convert to main coin
            CTxDB txDB("r");

            CTxIndex txIndex;
            if (txDB.ReadNewCoinGenesisTx(coinType.getSpendCoinType(), txIndex))
            {
                CTransaction newCoinGenesisTx;
                if (newCoinGenesisTx.ReadFromDisk(txIndex.pos))
                {
                    if (newCoinGenesisTx.isCreateNewCoin())
                    {
                        int64_t newCoinAmount = 0;
                        int64_t payCoinAmount = 0;

                        BOOST_FOREACH(const CTxOut &txOut, newCoinGenesisTx.vout)
                        {
                            if (txOut.getType() == TXOUT_NEW_COIN)
                                newCoinAmount += txOut.nValue;

                            if (txOut.getType() == TXOUT_NORMAL)
                                payCoinAmount += txOut.nValue;
                        }

                        float ratioNew2Main = (double)payCoinAmount / newCoinAmount;

                        feeVal = newCoinFee * ratioNew2Main;
                    }
                }
            }
        }

        if (feeVal == 0)
            throw logic_error("calculateTxFee(): error calcaulate!");

        feeVal = boost::algorithm::clamp<int64_t>(feeVal, MIN_FEE, MAX_FEE);

        return feeVal;
    }

    int64_t getFeeInTx(const CTransaction &tx)
    {
        if (tx.IsCoinBase() || tx.IsCoinStake())
            return 0;

        int64_t fee = 0;
        BOOST_FOREACH(const CTxOut &txOut, tx.vout)
        {
            if (txOut.getType() == TXOUT_FEE)
            {
                if (!isSentToPublicReceipt(txOut.scriptPubKey))
                    throw logic_error("getFeeInTx(): error receipt address check!");

                fee = txOut.nValue;

                break;
            }
        }

        return fee;
    }
}
