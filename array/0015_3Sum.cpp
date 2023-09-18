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
        std::vector<std::vector<int>> result;
        std::sort(nums.begin(), nums.end()); // arrange duplicates together
        // given nums[i], we are going to find nums[j] and nums[k],
        // s.t., nums[i] + nums[j] + nums[k] = 0, where
        // j != k, and both j and k are in the range [i+1, n)
        for (int i = 0; i <= n - 3; ++i) {
            if (i - 1 >= 0 && nums[i] == nums[i - 1])
                continue; // skip duplicates

            // optimization1:
            if (nums[i] + nums[i + 1] + nums[i + 2] > 0)
                break;

            // optimization2:
            if (nums[i] + nums[n - 2] + nums[n - 1] < 0)
                continue;

            const int target = -nums[i];
            // apply two-sum algorithm:
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                const int sum = nums[left] + nums[right];
                if (sum > target) {
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    result.push_back({nums[i], nums[left], nums[right]});
                    left++;
                    while (left < right && nums[left] == nums[left - 1]) {
                        left++;
                    }
                    right--;
                    while (left < right && nums[right] == nums[right + 1]) {
                        right--;
                    }
                }
            }
        }
        return result;
    }
};
