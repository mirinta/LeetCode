#include <unordered_map>
#include <vector>

/**
 * You are given an array of transactions transactions where transactions[i] = [from_i, toi,
 * amount_i] indicates that the person with ID = from_i gave amount_i $ to the person with ID = toi.
 *
 * Return the minimum number of transactions required to settle the debt.
 *
 * ! 1 <= transactions.length <= 8
 * ! transactions[i].length == 3
 * ! 0 <= from_i, to_i < 12
 * ! from_i != to_i
 * ! 1 <= amount_i <= 100
 */

class Solution
{
public:
    int minTransfers(std::vector<std::vector<int>>& transactions)
    {
        std::unordered_map<int, int> map;
        for (const auto& transaction : transactions) {
            const auto& from = transaction[0];
            const auto& to = transaction[1];
            const auto& amount = transaction[2];
            // "from" gave "to" amount of money
            map[from] -= amount;
            map[to] += amount;
        }
        // map[i] > 0 means i is a debtor
        // map[i] < 0 means i is a creditor
        std::vector<int> debts;
        for (const auto& [i, debt] : map) {
            if (debt != 0) {
                debts.push_back(debt);
            }
        }
        return backtrack(debts, 0);
    }

private:
    int backtrack(std::vector<int>& debts, int current)
    {
        while (current < debts.size() && debts[current] == 0) {
            current++;
        }
        if (current == debts.size())
            return 0;

        int count = INT_MAX;
        for (int i = current + 1; i < debts.size(); ++i) {
            if (debts[current] * debts[i] < 0) {
                debts[i] += debts[current];
                count = std::min(count, 1 + backtrack(debts, current + 1));
                debts[i] -= debts[current];
            }
        }
        return count;
    }
};