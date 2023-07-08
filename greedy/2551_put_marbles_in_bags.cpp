#include <algorithm>
#include <vector>

/**
 * You have k bags. You are given a 0-indexed integer array weights where weights[i] is the weight
 * of the ith marble. You are also given the integer k.
 *
 * Divide the marbles into the k bags according to the following rules:
 *
 * - No bag is empty.
 *
 * - If the ith marble and jth marble are in a bag, then all marbles with an index between the ith
 * and jth indices should also be in that same bag.
 *
 * - If a bag consists of all the marbles with an index from i to j inclusively, then the cost of
 * the bag is weights[i] + weights[j].
 *
 * The score after distributing the marbles is the sum of the costs of all the k bags.
 *
 * Return the difference between the maximum and minimum scores among marble distributions.
 *
 * ! 1 <= k <= weights.length <= 10^5
 * ! 1 <= weights[i] <= 10^9
 */

class Solution
{
public:
    long long putMarbles(std::vector<int>& weights, int k)
    {
        // [X1...X2] [Y1...Y2] [Z1...Z2]
        // - score1 = X1 + X2
        // - score2 = Y1 + Y2
        // - score3 = Z1 + Z2
        // - score = X1 + X2 + Y1 + Y2 + Z1 + Z2
        // both min(score) and max(score) have X1 and X2,
        // then diff = (X2 + Y1) + (Y2 + Z1),
        // it is the sum of adjacent values (at most k-1 pairs)
        std::vector<long long> adjacentSum;
        for (int i = 0; i < weights.size() - 1; ++i) {
            adjacentSum.push_back(weights[i] + weights[i + 1]);
        }
        std::sort(adjacentSum.begin(), adjacentSum.end());
        long long result = 0;
        for (int i = 0; i < k - 1; ++i) {
            result += adjacentSum[adjacentSum.size() - 1 - i];
        }
        for (int i = 0; i < k - 1; ++i) {
            result -= adjacentSum[i];
        }
        return result;
    }
};