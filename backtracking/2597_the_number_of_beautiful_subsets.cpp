#include <unordered_map>
#include <vector>

/**
 * You are given an array nums of positive integers and a positive integer k.
 *
 * A subset of nums is beautiful if it does not contain two integers with an absolute difference
 * equal to k.
 *
 * Return the number of non-empty beautiful subsets of the array nums.
 *
 * A subset of nums is an array that can be obtained by deleting some (possibly none) elements from
 * nums. Two subsets are different if and only if the chosen indices to delete are different.
 *
 * ! 1 <= nums.length <= 20
 * ! 1 <= nums[i], k <= 1000
 */

class Solution
{
public:
    int beautifulSubsets(std::vector<int>& nums, int k)
    {
        int result = 0;
        std::unordered_map<int, int> map;
        backtrack(result, map, 0, k, nums);
        return result - 1; // subtract empty set
    }

private:
    void backtrack(int& result, std::unordered_map<int, int>& map, int i, int k,
                   const std::vector<int>& nums)
    {
        if (i == nums.size()) {
            result++;
            return;
        }
        // case 1: nums[i] is not picked
        backtrack(result, map, i + 1, k, nums);
        // case 2: nums[i] is picked iff nums[i]-k and nums[i]+k are not picked
        if (map[nums[i] + k] <= 0 && map[nums[i] - k] <= 0) {
            map[nums[i]]++;
            backtrack(result, map, i + 1, k, nums);
            map[nums[i]]--;
        }
    }
};