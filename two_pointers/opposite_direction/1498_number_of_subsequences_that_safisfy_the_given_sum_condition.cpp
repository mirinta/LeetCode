#include <algorithm>
#include <vector>

/**
 * You are given an array of integers "nums" and an integer "target".
 *
 * Return the number of non-empty subsequences of "nums" such that the sum of the minimum and
 * maximum element on it is less or equal to target. Since the answer may be too large, return it
 * module 10^9 + 7.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 * ! 1 <= target <= 10^6
 */

class Solution
{
public:
    int numSubseq(std::vector<int>& nums, int target)
    {
        constexpr int kMod = 1e9 + 7;
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int lo = 0;
        int hi = n - 1;
        int result = 0;
        while (lo <= hi) {
            if (nums[lo] + nums[hi] > target) {
                hi--;
            } else {
                // count the number of subsequences starting with nums[lo]
                // each element in nums[lo+1:hi] has two choices: choose or ignore
                result = (result + powmod(2, hi - lo, kMod)) % kMod;
                lo++;
            }
        }
        return result;
    }

private:
    long long powmod(long long a, long long b, long long mod)
    {
        long long result = 1;
        long long base = a;
        while (b) {
            if (b & 1) {
                result = result * base % mod;
            }
            b >>= 1;
            base = base * base % mod;
        }
        return result;
    }
};