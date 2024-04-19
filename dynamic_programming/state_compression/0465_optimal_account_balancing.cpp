#include <unordered_map>
#include <vector>

/**
 * You are given an array of transactions transactions where transactions[i] = [fromi, toi, amounti]
 * indicates that the person with ID = fromi gave amounti $ to the person with ID = toi.
 *
 * Return the minimum number of transactions required to settle the debt.
 *
 * ! 1 <= transactions.length <= 8
 * ! transactions[i].length == 3
 * ! 0 <= fromi, toi < 12
 * ! fromi != toi
 * ! 1 <= amounti <= 100
 */

class Solution
{
public:
    int minTransfers(std::vector<std::vector<int>>& transactions)
    {
        return approach2(transactions);
    }

private:
    int approach2(const std::vector<std::vector<int>>& transactions)
    {
        std::unordered_map<int, int> map;
        for (const auto& trans : transactions) {
            map[trans[0]] -= trans[2];
            map[trans[1]] += trans[2];
        }
        std::vector<int> v;
        for (const auto& pair : map) {
            v.push_back(pair.second);
        }
        // dp[i] = min num of transactions to settle the debt of group i
        // given group i and debt[i] = 0,
        // find a subgroup j such that debt[j] = 0,
        // then dp[i] = min(dp[i], dp[j] + dp[i^j])
        const int n = v.size(); // num of people
        const int m = 1 << n;   // num of groups
        std::vector<int> debt(m, 0);
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) {
                    debt[i] += v[j];
                }
            }
        }
        std::vector<int> dp(m, INT_MAX / 2);
        dp[0] = 0;
        for (int i = 1; i < m; ++i) {
            if (debt[i] != 0)
                continue;

            // at most x-1 transactions to settle the debt of a group with x people
            dp[i] = numOfBinaryOnes(i) - 1;
            for (int sub = (i - 1) & i; sub > 0; sub = (sub - 1) & i) {
                if (debt[sub] == 0) {
                    dp[i] = std::min(dp[i], dp[sub] + dp[i ^ sub]);
                }
            }
        }
        return dp[m - 1];
    }

    int numOfBinaryOnes(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }

    int approach1(const std::vector<std::vector<int>>& transactions)
    {
        std::unordered_map<int, int> map;
        for (const auto& trans : transactions) {
            map[trans[0]] -= trans[2];
            map[trans[1]] += trans[2];
        }
        std::vector<int> debts;
        for (const auto& pair : map) {
            if (pair.second != 0) {
                debts.push_back(pair.second);
            }
        }
        return backtrack(debts, 0);
    }

    // min num of transactions to settle debts[i:n-1]
    int backtrack(std::vector<int>& debts, int i)
    {
        while (i < debts.size() && debts[i] == 0) {
            i++;
        }
        if (i == debts.size())
            return 0;

        int result = INT_MAX / 2;
        for (int j = i + 1; j < debts.size(); ++j) {
            if ((debts[i] ^ debts[j]) < 0) {
                debts[j] += debts[i];
                result = std::min(result, 1 + backtrack(debts, i + 1));
                debts[j] -= debts[i];
            }
        }
        return result;
    }
};