#include <algorithm>
#include <vector>

/**
 * Given an integer array "nums", return all the triplets "nums[i], nums[j], nums[k]" such that
 * "i != j, j != k", and "nums[i] + nums[j] + nums[k] == 0".
 *
 * ! 3 <= nums.length <= 3000
 * ! -10^5 <= nums[i] <= 10^5
 */

class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
    {
        if (nums.size() < 3)
            return {};

        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> result;
        for (int i = 0; i < n; ++i) {
            auto pairs = twoSum(i + 1, -nums[i], nums);
            if (pairs.empty())
                continue;

            for (auto& pair : pairs) {
                pair.push_back(nums[i]);
                result.push_back(std::move(pair));
            }
            // since the array is sorted, all duplicates of nums[i] are arranged together
            // move the pointer until we find a new number
            while (i + 1 < n && nums[i] == nums[i + 1]) {
                i++;
            }
        }
        return result;
    }

private:
    // find two numbers in nums[start:] that can add up to the "target"
    // nums is sorted in ascending order
    std::vector<std::vector<int>> twoSum(int start, int target, const std::vector<int>& nums)
    {
        if (nums.size() < 2)
            return {};

        std::vector<std::vector<int>> result;
        int left = start;
        int right = nums.size() - 1;
        while (left < right) {
            const int leftVal = nums[left];
            const int rightVal = nums[right];
            const int sum = leftVal + rightVal;
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
                while (left < right && nums[left] == leftVal) {
                    left++;
                }
                while (left < right && nums[right] == rightVal) {
                    right--;
                }
            }
        }
        return result;
    }
};
