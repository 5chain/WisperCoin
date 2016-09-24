//
// Created by LiSuyong on 9/24/16.
//

#include "MultiCoins.h"
#include "txdb.h"
#include "main.h"

namespace MultiCoins
{
    static int64_t calculateTxFee(const string &coinTypeStr, int64_t amount)
    {
        int64_t feeVal = 0;

        CoinType coinType(coinTypeStr);
        if (coinType.isCreateNewCoin())
        {
            feeVal = createNewCoinFee;
        }
        else if (coinType.isMainCoinType())
        {
            feeVal = amount * feeRatio;
        }
        else // This is for new coin transactions.
        {
            int64_t newCoinFee = amount * feeRatio;

            // Then convert to main coin
            CTxDB txDB("r");

            CTxIndex txIndex;
            if (txDB.ReadNewMultiCoinGenesisTx(coinType.getSpendCoinType(), txIndex))
            {
                CTransaction tx;
                if (tx.ReadFromDisk(txIndex.pos))
                {
                    // See createNewCoinTx() description.
                    if (tx.vout.size() == 3)
                    {
                        float ratioNew2Main = (float) ((double) tx.vout[0].nValue / tx.vout[2].nValue);

                        feeVal = newCoinFee * ratioNew2Main;
                    }
                }
            }
        }

        if (isFeeValid(feeVal))
            return feeVal;

        // else throw...
        throw logic_error("calculateTxFee(): error calcaulate!");
    }
}
