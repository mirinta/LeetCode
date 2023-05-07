#include <vector>

/**
 * Given an integer array "nums", return the length of the longest strictly increasing subsequence.
 *
 * ! Can you come up with an algorithm that runs in O(nlogn) time complexity?
 *
 * Example:
 * Input: nums = [10, 9, 2, 5, 3, 7, 101, 18]
 * Output: 4
 * Explanation: the longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4.
 */

class Solution
{
public:
    // similar to No.1964
    int lengthOfLIS(std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        std::vector<int> arr; // maintain arr in strictly increasing order
        for (const auto& val : nums) {
            if (arr.empty() || val > arr.back()) {
                arr.push_back(val);
            } else {
                const auto j = lowerBound(arr, val);
                if (j < 0)
                    continue;

                arr[j] = val;
            }
        }
        return arr.size();
    }

private:
    // the input arr is sorted in strictly increasing order
    // find the first position j s.t. arr[j] >= val
    int lowerBound(std::vector<int>& arr, int val)
    {
        if (arr.empty())
            return -1;

        int left = 0;
        int right = arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < val) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left == arr.size() ? -1 : left;
    }
};