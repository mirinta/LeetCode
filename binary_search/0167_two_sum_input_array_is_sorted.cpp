#include <vector>

/**
 * Given a 1-indexed array of integers "numbers" that is already sorted in non-decreasing order,
 * find two numbers such that they add up to a specific "target" number. Let these two numbers be
 * "numbers[index1]" and "numbers[index2]" where 1 <= index1 < index2 <= numbers.length.
 *
 * Return the indicies of the two numbers, "index1" and "index2", added by one as an integer array
 * "[index1, index2]" of length 2.
 *
 * The tests are generated such that there is exactly one solution.
 *
 * ! "numbers" is sorted in non-decreasing order.
 *
 * ! "index1" and "index2" are 1-indexed.
 *
 * ! You may not use the same element twice.
 *
 * ! Your solution must use only constant extra place.
 */

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target)
    {
        // two pointers: forward and backward
        // check sum = nums[forward] + nums[backward]
        // - if sum = target, done;
        // - if sum < target, forward++ (because the array is sorted in non-decreasing order), next
        // loop;
        // - if sum > target, backward--, next loop;
        int forward = 0;
        int backward = numbers.size() - 1;
        while (forward < backward) {
            const auto sum = numbers[forward] + numbers[backward];
            if (sum == target)
                return {forward + 1, backward + 1};

            if (sum < target) {
                forward++;
            } else {
                backward--;
            }
        }
        return {};
    }
};