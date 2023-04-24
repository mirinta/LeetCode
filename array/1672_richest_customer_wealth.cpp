#include <vector>

/**
 * You are given an "m x n" integer grid "accounts" where "accounts[i][j]" is the amount of money
 * the "i"th customer has in the "j"th bank. Return the wealth that the richest customer has.
 *
 * A customer's wealth is the amount of money they have in all their bank account. The richest
 * customer is the customer that has the maximum wealth.
 */

class Solution
{
public:
    int maximumWealth(std::vector<std::vector<int>>& accounts)
    {
        int result = INT_MIN;
        for (size_t i = 0; i < accounts.size(); ++i) {
            int sum = 0;
            for (size_t j = 0; j < accounts[i].size(); ++j) {
                sum += accounts[i][j];
            }
            result = std::max(result, sum);
        }
        return result;
    }
};