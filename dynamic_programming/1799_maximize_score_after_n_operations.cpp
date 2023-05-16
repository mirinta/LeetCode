#include <numeric>
#include <vector>

/**
 * You are given "nums", an array of positive integers of size "2 * n". You must perform "n"
 * operations on this array.
 *
 * In the ith operation (1-indexed), you will:
 *
 * - Choose two elements, x and y.
 *
 * - Receive a score of i * gcd(x, y).
 *
 * - Remove x and y from nums.
 *
 * Return the maximum score you can receive after performing "n" operations.
 *
 * The function gcd(x, y) is the greatest common divisor of x and y.
 */

class Solution
{
    // index = [3, 2, 1, 0], in reverse order
    // nums  = [3, 4, 6, 8]
    // mask  = [0, 0, 0, 0], reinterpret to int is 0
    // ----- 1. pick numbers -----
    // pick 4 (index = 2): mask_4 = [0, 1, 0, 0], reinterpret to int is (1 << 2) = 4
    // pick 6 (index = 1): mask_6 = [0, 0, 1, 0], reinterpret to int is (1 << 1) = 2
    // pick 4 and 6: mask_4_6 = [0, 1, 1, 0], reinterpret to int is (mask_4 | mask_6) = 6
    // ----- 2. check a number is picked -----
    // given mask = 6 = [0, 1, 1, 0], check value 1 (index = 3) is picked:
    // (6 >> 3) = [0, 0, 0, 0] = 0, it means value 1 is not picked
public:
    int maxScore(std::vector<int>& nums)
    {
        // number of values = M = number of bits of "mask"
        // each bit has two choices: 0 or 1
        // there are 2^M values, "mask" in range [0, 2^M - 1]
        const int size = 1 << nums.size();
        std::vector<int> memo(size, -1);
        return dp(nums, 0, 0, memo);
    }

private:
    int dp(std::vector<int>& nums, int mask, int pairsPicked, std::vector<int>& memo)
    {
        if (2 * pairsPicked == nums.size())
            return 0;

        if (memo[mask] != -1)
            return memo[mask];

        int maxScore = 0;
        // pick value in reverse order:
        // 1 << 0 means the nums[size - 1] is picked
        for (int first = 0; first < nums.size(); ++first) {
            for (int second = first + 1; second < nums.size(); ++second) {
                if (((mask >> first) & 1) == 1 || ((mask >> second) & 1) == 1)
                    continue;

                int newMask = mask | ((1 << first) | (1 << second));
                int currentScore = (pairsPicked + 1) * std::gcd(nums[first], nums[second]);
                int remainingScore = dp(nums, newMask, pairsPicked + 1, memo);
                maxScore = std::max(maxScore, currentScore + remainingScore);
            }
        }
        memo[mask] = maxScore;
        return maxScore;
    }
};