#include <unordered_map>
#include <vector>

/**
 * Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that
 * the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.
 *
 * Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.
 *
 * A subarray is defined as a contiguous block of elements in the array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= p <= 10^9
 */

class Solution
{
public:
    int minSubarray(std::vector<int>& nums, int p)
    {
        // let sum[i] = sum of nums[0:i]
        // suppose we remove subarray nums[j:i]
        // sum of remaining elements = sum[n-1] - (sum[i] - sum[j-1])
        // the sum is divisible by p:
        // (sum[i] - sum[n-1]) % p = sum[j-1] % p
        // (sum[i] % k - sum[n-1] % k) % p = sum[j-1] % p
        const int n = nums.size();
        int total = 0;
        for (const auto& val : nums) {
            total = (total + val) % p;
        }
        if (total == 0)
            return 0;

        std::unordered_map<int, int> map;
        map[0] = -1; // sum[i] % k = 0, length = i+1, j=-1
        int sum = 0;
        int result = INT_MAX;
        for (int i = 0; i < n; ++i) {
            sum = (sum + nums[i]) % p;
            const int target = (sum - total + p) % p;
            if (map.find(target) != map.end()) {
                result = std::min(result, i - map[target]);
            }
            map[sum] = i;
        }
        return result >= n ? -1 : result;
    }
};