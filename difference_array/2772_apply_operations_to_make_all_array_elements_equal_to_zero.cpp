#include <vector>

/**
 * You are given a 0-indexed integer array nums and a positive integer k.
 *
 * You can apply the following operation on the array any number of times:
 *
 * - Choose any subarray of size k from the array and decrease all its elements by 1.
 *
 * Return true if you can make all the array elements equal to 0, or false otherwise.
 *
 * A subarray is a contiguous non-empty part of an array.
 *
 * ! 1 <= k <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^6
 */

class Solution
{
public:
    bool checkArray(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        // diff[i] = num of operations of nums[i] - num of operations of nums[i-1]
        std::vector<int> diff(n + 1, 0);
        // the first operation: decrease nums[0:k-1] by nums[0] times
        diff[0] = nums[0];
        diff[k] = -nums[0];
        for (int i = 1; i < n; ++i) {
            diff[i] += diff[i - 1]; // diff[i] becomes the actual num of operations on nums[i]
            if (diff[i] == nums[i])
                continue;

            if (nums[i] < diff[i] || i + k - 1 >= n)
                return false;

            const int delta = nums[i] - diff[i]; // remaining num of operations to make nums[i] = 0
            diff[i] += delta;
            diff[i + k] -= delta;
        }
        return true;
    }
};