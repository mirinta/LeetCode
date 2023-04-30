#include <algorithm>
#include <vector>

/**
 * Given an integer array "nums", return all the triplets "nums[i], nums[j], nums[k]" such that
 * "i != j, j != k", and "nums[i] + nums[j] + nums[k] == 0".
 */

class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
    {
        if (nums.empty() || nums.size() < 3)
            return {};

        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> result;
        for (size_t i = 0; i < nums.size(); ++i) {
            auto pairs = twoSum(nums, -nums[i], i + 1);
            if (pairs.empty())
                continue;

            for (auto& pair : pairs) {
                pair.push_back(nums[i]);
                result.push_back(std::move(pair));
            }
            // skip same value to avoid duplicates
            while (i < nums.size() - 1 && nums[i] == nums[i + 1]) {
                i++;
            }
        }
        return result;
    }

private:
    // find nums[i] + nums[j] = target, without duplicates
    // the input array should be sorted in ascending order
    std::vector<std::vector<int>> twoSum(std::vector<int>& nums, int target, int start)
    {
        if (nums.size() < 2)
            return {};

        std::vector<std::vector<int>> result;
        int low = start;
        int high = nums.size() - 1;
        while (low < high) {
            const auto& left = nums[low];
            const auto& right = nums[high];
            const auto sum = left + right;
            if (sum > target) {
                while (low < high && nums[high] == right) {
                    high--;
                }
            } else if (sum < target) {
                while (low < high && nums[low] == left) {
                    low++;
                }
            } else {
                result.push_back({left, right});
                while (low < high && nums[low] == left) {
                    low++;
                }
                while (low < high && nums[high] == right) {
                    high--;
                }
            }
        }
        return result;
    }
};