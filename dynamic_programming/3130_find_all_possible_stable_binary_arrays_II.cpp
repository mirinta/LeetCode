#include <cstring>

/**
 * You are given 3 positive integers zero, one, and limit.
 *
 * A binary array arr is called stable if:
 *
 * - The number of occurrences of 0 in arr is exactly zero.
 *
 * - The number of occurrences of 1 in arr is exactly one.
 *
 * - Each subarray of arr with a size greater than limit must contain both 0 and 1.
 *
 * Return the total number of stable binary arrays.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= zero, one, limit <= 1000
 */

class Solution
{
public:
    int numberOfStableArrays(int zero, int one, int limit)
    {
        std::memset(memo, -1, sizeof(memo));
        int result = 0;
        result = (result + dfs(zero, one, 0, limit)) % kMod;
        result = (result + dfs(zero, one, 1, limit)) % kMod;
        return result;
    }

private:
    static constexpr int kMod = 1e9 + 7;
    long long memo[1001][1001][2];

    // total num of valid arrays can be built with i 0's and j 1's
    // and the last element is k (0 or 1)
    long long dfs(int i, int j, int k, int limit)
    {
        if (i < 0 || j < 0)
            return 0;

        if (i == 0)
            return k == 1 && j <= limit;

        if (j == 0)
            return k == 0 && i <= limit;

        if (memo[i][j][k] != -1)
            return memo[i][j][k];

        long long result = 0;
        if (k == 0) {
            // X X X X X X X 1 [0]
            result = (result + dfs(i - 1, j, 1, limit)) % kMod;
            // X 1 0 0 ... 0 0 [0]
            //     |<-limit->|
            result = (result + dfs(i - 1, j, 0, limit)) % kMod;
            result = (result - dfs(i - limit - 1, j, 1, limit) + kMod) % kMod;
        } else {
            // X X X X X X X 0 [1]
            result = (result + dfs(i, j - 1, 0, limit)) % kMod;
            // X 0 1 1 ... 1 1 [1]
            //     |<-limit->|
            result = (result + dfs(i, j - 1, 1, limit)) % kMod;
            result = (result - dfs(i, j - limit - 1, 0, limit) + kMod) % kMod;
        }
        return memo[i][j][k] = result;
    }
};