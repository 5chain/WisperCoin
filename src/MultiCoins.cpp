//
// Created by LiSuyong on 9/24/16.
//

#include "MultiCoins.h"
#include "txdb.h"
#include "main.h"

#include <boost/algorithm/clamp.hpp>

namespace MultiCoins
{
    static int64_t calculateTxFee(const CTransaction &tx)
    {
        int64_t feeVal = 0;

        if (tx.isCreateNewCoin())
        {
            feeVal = createNewCoinFee;
        }
        else if (tx.isMainCoinType())
        {
            int64_t amount = 0;
//            for (int id = 0, size = tx.vin.size(); id < size - 1; ++id)
//            {
//                amount += tx.vin
//            }

            feeVal = amount * feeRatio;
        }
        else // This is for new coin transactions.
        {
            int64_t amount = 0;

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
        const CTxOut &txOut = tx.vout[tx.getFeeOutIdx()];

        CTxDestination address;
        if (!ExtractDestination(txOut.scriptPubKey, address) || !isSentToReceiptAddress(address))
            throw logic_error("getFeeInTx(): error receipt address check!");

        return txOut.nValue;
    }
}
