#include <string>
#include <vector>

/**
 * You are given a sorted unique integer array "nums".
 *
 * A range [a, b] is the set of all integers from a to b (inclusive).
 *
 * Return the smallest sorted list of ranges that cover all the numbers in the array exactly. That
 * is, each element of nums is covered by exactly one of the ranges, and there is no integer x such
 * that x is in one of the ranges but not in nums.
 *
 * Each range [a, b] in the list should be output as:
 *
 * - "a->b" if a != b
 *
 * - "a" if a == b
 *
 * ! 0 <= nums.length <= 20
 * ! -2^31 <= nums[i] <= 2^31 - 1
 * ! All the values of nums are unique.
 * ! nums is sorted in ascending order.
 *
 * Example:
 * Input: nums = [0,2,3,4,6,8,9]
 * Output: ["0","2->4","6","8->9"]
 * Explanation: The ranges are:
 * [0,0] --> "0"
 * [2,4] --> "2->4"
 * [6,6] --> "6"
 * [8,9] --> "8->9"
 */

class Solution
{
public:
    std::vector<std::string> summaryRanges(const std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        if (nums.size() == 1)
            return {std::to_string(nums[0])};

        std::vector<std::string> result;
        for (int i = 0; i < nums.size(); ++i) {
            int start = nums[i];
            // 0,  1,  2,  4,  5,  7
            // ^       ^
            // start   i
            while (i + 1 < nums.size() && nums[i] + 1 == nums[i + 1]) {
                i++;
            }
            std::string s = std::to_string(start);
            if (start != nums[i]) {
                s.append("->");
                s.append(std::to_string(nums[i]));
            }
            result.push_back(std::move(s));
        }
        return result;
    }
};
