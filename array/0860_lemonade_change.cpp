#include <cstddef>
#include <vector>

/**
 * At a lemonade stand, each lemonade costs $5. Customers are standing in a queue to buy from you
 * and order one at a time (in the order specified by bills). Each customer will only buy one
 * lemonade and pay with either a $5, $10, or $20 bill. You must provide the correct change to each
 * customer so that the net transaction is that the customer pays $5. Note that you do not have any
 * change in hand at first.
 *
 * Given an integer array bills where bills[i] is the bill the ith customer pays, return true if you
 * can provide every customer with the correct change, or false otherwise.
 *
 * ! bills[i] is either 5, 10, or 20.
 */

class Solution
{
public:
    bool lemonadeChange(const std::vector<int>& bills)
    {
        // change = bill - 5
        // - bill is either 5, 10, or 20, then change is either 5 or 15
        // - 15 can be made up of 5+10 or 5+5+5
        int receivedFive = 0;
        int receivedTen = 0;
        for (const auto& bill : bills) {
            switch (bill) {
            case 5:
                receivedFive++;
                break;
            case 10:
                if (receivedFive < 1)
                    return false;

                receivedFive--;
                receivedTen++;
                break;
            case 20:
                if (receivedFive > 0 && receivedTen > 0) {
                    receivedFive--;
                    receivedTen--;
                } else if (receivedFive >= 3) {
                    receivedFive -= 3;
                } else {
                    return false;
                }
            default:
                break;
            }
        }
        return true;
    }
};