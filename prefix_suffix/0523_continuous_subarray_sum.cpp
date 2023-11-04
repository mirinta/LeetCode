#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums and an integer k, return true if nums has a good subarray or false
 * otherwise.
 *
 * A good subarray is a subarray where:
 *
 * - its length is at least two, and
 *
 * - the sum of the elements of the subarray is a multiple of k.
 *
 * Note that:
 *
 * - A subarray is a contiguous part of the array.
 *
 * - An integer x is a multiple of k if there exists an integer n such that x = n * k. 0 is always a
 * multiple of k.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 * ! 0 <= sum(nums[i]) <= 2^31 - 1
 * ! 1 <= k <= 2^31 - 1
 */

class Solution
{
public:
    bool checkSubarraySum(std::vector<int>& nums, int k)
    {
        // 0 X ... X X j-1 j X X ... X i
        // |<--prefix'-->| |<--target->|
        // |<---------prefix-------->|
        // - Assume there is a subarray nums[j:i],
        //   let prefix'=sum[0:j-1] and prefix=sum[j:i]
        //   then the sum of this subarray is prefix-prefix'.
        // - If the sum of this subarray is a multiple of k,
        //   then prefix-prefix' is a multiple of k,
        //   it means prefix % k = prefix' % k.
        std::unordered_map<int, int> map; // remainder to index j
        map[0] = 0;
        int prefix = 0;
        for (int i = 0; i < nums.size(); ++i) {
            prefix += nums[i];
            const int remainder = prefix % k;
            if (!map.count(remainder)) {
                map[remainder] = i + 1;
            } else if (i - map[remainder] + 1 >= 2)
                return true;
        }
        return false;
    }
};