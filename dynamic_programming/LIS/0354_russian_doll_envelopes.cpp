#include <algorithm>
#include <vector>

/**
 * You are given a 2D array of integers "envelopes" where "envelopes[i] = [wi, hi]" represents the
 * width and the height of an envelope.
 *
 * One envelope can fit into another if and only if both the width and the height of one envelope
 * are greater than the other envelope's width and height.
 *
 * Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
 *
 * ! Note: you cannot rotate an envelope.
 */

class Solution
{
    // after sorting:
    // width    height
    // [1         8]
    // [2         3] <-
    // [5         4] <-
    // [5         2]
    // [6         7] <-
    // [6         4]
    // LIS of the height array is [3, 4, 7]
    // maxEnvelopes = 3, the length of [3, 4, 7]
public:
    int maxEnvelopes(std::vector<std::vector<int>>& envelopes)
    {
        if (envelopes.empty())
            return 0;

        // sort width in ascending order
        // if two envelopes have the same width,
        // then sort their heights in descending order
        std::sort(envelopes.begin(), envelopes.end(), [](const auto& e1, const auto& e2) {
            return e1[0] == e2[0] ? e1[1] > e2[1] : e1[0] < e2[0];
        });
        // find LIS in sorted heights, the length is the result
        std::vector<int> heights(envelopes.size());
        for (size_t i = 0; i < envelopes.size(); ++i) {
            heights[i] = envelopes[i][1];
        }
        return lengthOfLIS(heights); // see LC 300
    }

private:
    int lengthOfLIS(const std::vector<int>& nums)
    {
        const auto size = nums.size();
        if (size < 1)
            return size;

        std::vector<int> ascending; // strictly increasing
        for (const auto& val : nums) {
            if (ascending.empty() || val > ascending.back()) {
                ascending.push_back(val);
                continue;
            }
            if (const auto pos = findPos(ascending, val); pos >= 0) {
                ascending[pos] = val;
            }
        }
        return ascending.size();
    }

    // find the first position j in nums s.t. nums[j] > val
    int findPos(const std::vector<int>& nums, int val)
    {
        if (nums.empty())
            return -1;

        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= val) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } // the loop is terminated when left = right + 1
        return left == nums.size() ? -1 : left;
    }
};
