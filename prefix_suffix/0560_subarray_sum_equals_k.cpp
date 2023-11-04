#include <unordered_map>
#include <vector>

/**
 * Given an array of integers nums and an integer k, return the total number of subarrays whose sum
 * equals to k.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 2 * 10^4
 * ! -1000 <= nums[i] <= 1000
 * ! -10^7 <= k <= 10^7
 */

class Solution
{
public:
    int subarraySum(std::vector<int>& nums, int k)
    {
        // START ... Z Z X X X X ... X
        // |<-prefix'->| |<--target->|
        // |<---------prefix-------->|
        std::unordered_map<int, int> map;
        map[0] = 1;
        int prefix = 0;
        int result = 0;
        for (const auto& val : nums) {
            prefix += val;
            const int diff = prefix - k;
            if (map.count(diff)) {
                result += map[diff];
            }
            map[prefix]++;
        }
        return result;
    }
};