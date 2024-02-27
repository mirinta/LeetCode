#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed integer array nums, an integer modulo, and an integer k.
 *
 * Your task is to find the count of subarrays that are interesting.
 *
 * A subarray nums[l..r] is interesting if the following condition holds:
 *
 * Let cnt be the number of indices i in the range [l, r] such that nums[i] % modulo == k. Then, cnt
 * % modulo == k. Return an integer denoting the count of interesting subarrays.
 *
 * Note: A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= modulo <= 10^9
 * ! 0 <= k < modulo
 */

class Solution
{
public:
    long long countInterestingSubarrays(std::vector<int>& nums, int modulo, int k)
    {
        // let count[i] = num of elements in nums[0:i] such that each element % mod = k
        // if nums[j+1:i] is a valid subarray,
        // then (count[i] - count[j]) % mod = k
        // count[i] - count[j] = A*mod + k
        // count[i] - A*mod - k = count[j]
        // (count[i] % mod - k % mod) % mod = count[j] % mod
        // since k < mod, then k % mod = k
        // (count[i] % mod - k) % mod = count[j] % mod
        const int n = nums.size();
        std::unordered_map<int, long long> map;
        // base case: nums[0:i] is a valid subarray, then count[i] % mod = k
        // then (count[i] % mod - k) % mod = 0, thus, map[0] = 1
        map[0] = 1;
        int count = 0;
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            count += nums[i] % modulo == k;
            const int target = (count % modulo - k + modulo) % modulo;
            if (map.count(target)) {
                result += map[target];
            }
            map[count % modulo]++;
        }
        return result;
    }
};