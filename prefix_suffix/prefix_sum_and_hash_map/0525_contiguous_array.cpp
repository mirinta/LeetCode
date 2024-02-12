#include <unordered_map>
#include <vector>

/**
 * Given a binary array nums, return the maximum length of a contiguous subarray with an equal
 * number of 0 and 1.
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums[i] is either 0 or 1.
 */

class Solution
{
public:
    int findMaxLength(std::vector<int>& nums)
    {
        // let sum[i] = sum of nums[0:i], if nums[j] = 0, let sum += -1
        // if map[sum[i]] = j, then sum[i] - sum[j] = 0
        // it means sum of nums[j+1:i] = 0, i.e., nums[j+1:i] has equal num of 0 and 1
        // length of this subarray = i-j
        // corner case: sum[i] = 0, length of nums[0:i] = i+1
        // thus, we initialize map[0] = -1
        const int n = nums.size();
        std::unordered_map<int, int> map;
        map[0] = -1;
        int sum = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i] == 0 ? -1 : 1;
            if (map.find(sum) == map.end()) {
                map[sum] = i;
            } else {
                result = std::max(result, i - map[sum]);
            }
        }
        return result;
    }
};