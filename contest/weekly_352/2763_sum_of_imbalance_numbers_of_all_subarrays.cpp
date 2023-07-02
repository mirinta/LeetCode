#include <unordered_set>
#include <vector>

/**
 * The imbalance number of a 0-indexed integer array arr of length n is defined as the number of
 * indices in sarr = sorted(arr) such that:
 *
 * - 0 <= i < n - 1, and
 *
 * - sarr[i+1] - sarr[i] > 1
 *
 * Here, sorted(arr) is the function that returns the sorted version of arr.
 *
 * Given a 0-indexed integer array nums, return the sum of imbalance numbers of all its subarrays.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= nums.length
 */

class Solution
{
public:
    int sumImbalanceNumbers(std::vector<int>& nums)
    {
        int result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            std::unordered_set<int> set;
            set.insert(nums[i]);
            for (int j = i + 1, count = 0; j < nums.size(); ++j) {
                if (!set.count(nums[j])) {
                    set.insert(nums[j]);
                    count += 1 - set.count(nums[j] + 1) - set.count(nums[j] - 1);
                }
                result += count;
            }
        }
        return result;
    }
};