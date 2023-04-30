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
 */

class Solution
{
public:
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target)
    {
        std::sort(nums.begin(), nums.end());
        return nSum(nums, target, 4, 0);
    }

private:
    // the input array should be sorted in ascending order
    std::vector<std::vector<int>> nSum(std::vector<int>& nums, long long target, int n, int start)
    {
        if (nums.empty() || nums.size() < n)
            return {};

        std::vector<std::vector<int>> result;
        if (n == 2) {
            int low = start;
            int high = nums.size() - 1;
            while (low < high) {
                const auto& valLeft = nums[low];
                const auto& valRight = nums[high];
                const long long sum = valLeft + valRight;
                if (sum > target) {
                    while (low < high && nums[high] == valRight) {
                        high--;
                    }
                } else if (sum < target) {
                    while (low < high && nums[low] == valLeft) {
                        low++;
                    }
                } else {
                    result.push_back({valLeft, valRight});
                    while (low < high && nums[low] == valLeft) {
                        low++;
                    }
                    while (low < high && nums[high] == valRight) {
                        high--;
                    }
                }
            }
        } else {
            for (int i = start; i < nums.size(); ++i) {
                auto subResults = nSum(nums, target - nums[i], n - 1, i + 1);
                for (auto& sub : subResults) {
                    sub.push_back(nums[i]);
                    result.push_back(std::move(sub));
                }
                while (i < nums.size() - 1 && nums[i] == nums[i + 1]) {
                    i++;
                }
            }
        }
        return result;
    }
};