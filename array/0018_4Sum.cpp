#include <algorithm>
#include <vector>

/**
 * Given an array "nums" of "n" integers, return an array of all the unique quadruplets "nums[a],
 * nums[b], nums[c], nums[d]" such that:
 *
 * - 0 <= a, b, c, d < n
 *
 * - a, b, c and d are distinct
 *
 * - nums[a] + nums[b] + nums[c] + nums[d] = target
 *
 * You may return the answer in any order.
 *
 * ! 1 <= nums.length <= 200
 * ! -10^9 <= nums[i] <= 10^9
 * ! -10^9 <= target <= 10^9
 */

class Solution
{
public:
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target)
    {
        if (nums.size() < 4)
            return {};

        std::sort(nums.begin(), nums.end());
        return nSum(0, target, 4, nums);
    }

private:
    std::vector<std::vector<int>> nSum(int start, long long target, int n,
                                       const std::vector<int>& nums)
    {
        if (nums.size() - start < n)
            return {};

        std::vector<std::vector<int>> result;
        if (n == 2) {
            int left = start;
            int right = nums.size() - 1;
            while (left < right) {
                const int leftVal = nums[left];
                const int rightVal = nums[right];
                const long long sum = leftVal + rightVal;
                if (sum > target) {
                    while (left < right && nums[right] == rightVal) {
                        right--;
                    }
                } else if (sum < target) {
                    while (left < right && nums[left] == leftVal) {
                        left++;
                    }
                } else {
                    result.push_back({leftVal, rightVal});
                    while (left < right && nums[right] == rightVal) {
                        right--;
                    }
                    while (left < right && nums[left] == leftVal) {
                        left++;
                    }
                }
            }
        } else {
            for (int i = start; i < nums.size(); ++i) {
                auto subResults = nSum(i + 1, target - nums[i], n - 1, nums);
                if (subResults.empty())
                    continue;

                for (auto& sub : subResults) {
                    sub.push_back(nums[i]);
                    result.push_back(std::move(sub));
                }
                while (i + 1 < nums.size() && nums[i] == nums[i + 1]) {
                    i++;
                }
            }
        }
        return result;
    }
};
