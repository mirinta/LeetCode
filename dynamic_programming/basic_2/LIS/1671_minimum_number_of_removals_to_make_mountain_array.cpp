#include <vector>

/**
 * You may recall that an array arr is a mountain array if and only if:
 *
 * - arr.length >= 3
 *
 * - There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
 *
 *   - arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
 *
 *   - arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 *
 * Given an integer array nums​​​, return the minimum number of elements to remove to make
 * nums​​​ a mountain array.
 *
 * ! 3 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 10^9
 * ! It is guaranteed that you can make a mountain array out of nums.
 */

class Solution
{
public:
    int minimumMountainRemovals(std::vector<int>& nums)
    {
        // Li1 = length of the longest strictly increasing subsequence ending at nums[i]
        // Li2 = length of the longest strictly decreasing subsequence starting at nums[i]
        // num of elements to remove to make nums[i] as the peak element = N+1-Li1-Li2
        const int n = nums.size();
        const auto LIS = getLIS(nums);
        std::reverse(nums.begin(), nums.end());
        auto LDS = getLIS(nums);
        std::reverse(LDS.begin(), LDS.end());
        int result = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (LIS[i] >= 2 && LDS[i] >= 2) {
                result = std::min(result, n + 1 - LIS[i] - LDS[i]);
            }
        }
        return result;
    }

private:
    // return[i] = length of LIS ending at nums[i], same as LC.300
    // time O(NlogN), space O(N)
    std::vector<int> getLIS(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n);
        std::vector<int> vec; // strictly increasing
        for (int i = 0; i < n; ++i) {
            if (vec.empty() || vec.back() < nums[i]) {
                vec.push_back(nums[i]);
                result[i] = vec.size();
            } else {
                // iter != vec.end() is guaranteed
                // if not, it means all vec[i] < nums[i]
                // this case is handled in the above branch
                auto iter = std::lower_bound(vec.begin(), vec.end(), nums[i]);
                *iter = nums[i];
                result[i] = std::distance(vec.begin(), iter) + 1;
            }
        }
        return result;
    }
};