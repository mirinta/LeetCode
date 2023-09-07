#include <numeric>
#include <vector>

/**
 * There are n children standing in a line. Each child is assigned a rating value given in the
 * integer array ratings.
 *
 * You are giving candies to these children subjected to the following requirements:
 *
 * - Each child must have at least one candy.
 *
 * - Children with a higher rating get more candies than their neighbors.
 *
 * Return the minimum number of candies you need to have to distribute the candies to the children.
 *
 * ! n == ratings.length
 * ! 1 <= n <= 2 * 10^4
 * ! 0 <= ratings[i] <= 2 * 10^4
 */

class Solution
{
public:
    int candy(std::vector<int>& ratings)
    {
        const int n = ratings.size();
        std::vector<int> candies(n, 1);
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = 1 + candies[i - 1];
            }
        }
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = std::max(candies[i], 1 + candies[i + 1]);
            }
        }
        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};