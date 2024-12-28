#include <unordered_map>
#include <vector>

/**
 * You are given an array of positive integers nums and want to erase a subarray containing unique
 * elements. The score you get by erasing the subarray is equal to the sum of its elements.
 *
 * Return the maximum score you can get by erasing exactly one subarray.
 *
 * An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if
 * it is equal to a[l],a[l+1],...,a[r] for some (l,r).
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^4
 */

class Solution
{
public:
    int maximumUniqueSubarray(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        int sum = 0;
        int result = INT_MIN;
        for (int left = 0, right = 0; right < n; ++right) {
            map[nums[right]]++;
            sum += nums[right];
            while (map[nums[right]] > 1) {
                sum -= nums[left];
                if (--map[nums[left]] == 0) {
                    map.erase(nums[left]);
                }
                left++;
            }
            result = std::max(result, sum);
        }
        return result;
    }
};