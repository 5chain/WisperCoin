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
    static int64_t calculateTxFee(const CTransaction &tx)
    {
        if (tx.IsCoinBase() || tx.IsCoinStake())
            return 0;

        int64_t feeVal = 0;

        if (tx.isCreateNewCoin())
        {
            feeVal = createNewCoinFee;
        }
        else if (tx.isMainCoinTx())
        {
            int64_t amount = 0;
            BOOST_FOREACH(const CTxOut &txOut, tx.vout)
            {
                if (txOut.getType() == TXOUT_NORMAL)
                    amount += txOut.nValue;
            }

            feeVal = amount * feeRatio;
        }
        else // This is for new coin transactions.
        {
            int64_t amount = 0;
            BOOST_FOREACH(const CTxOut &txOut, tx.vout)
            {
                if (txOut.getType() == TXOUT_NORMAL)
                    amount += txOut.nValue;
            }

            int64_t newCoinFee = amount * feeRatio;

            // Then convert to main coin
            CTxDB txDB("r");

            CTxIndex txIndex;
            if (txDB.ReadNewCoinGenesisTx(tx.getSpendCoinType(), txIndex))
            {
                CTransaction newCoinGenesisTx;
                if (newCoinGenesisTx.ReadFromDisk(txIndex.pos))
                {
                    // See createNewCoinTx() description.
                    if (newCoinGenesisTx.vout.size() == 3)
                    {
                        float ratioNew2Main = (double)newCoinGenesisTx.vout[0].nValue / newCoinGenesisTx.vout[2].nValue;

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

    static int64_t getFeeInTx(const CTransaction &tx)
    {
        if (tx.IsCoinBase() || tx.IsCoinStake())
            return 0;

        int64_t fee = 0;
        BOOST_FOREACH(const CTxOut &txOut, tx.vout)
        {
            if (txOut.getType() == TXOUT_FEE)
            {
                CTxDestination address;
                if (!ExtractDestination(txOut.scriptPubKey, address) || !isSentToReceiptAddress(address))
                    throw logic_error("getFeeInTx(): error receipt address check!");

                fee = txOut.nValue;

                break;
            }
        }

        return fee;
    }
}
