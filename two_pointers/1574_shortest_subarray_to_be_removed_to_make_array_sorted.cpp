#include <vector>

/**
 * Given an integer array arr, remove a subarray (can be empty) from arr such that the remaining
 * elements in arr are non-decreasing.
 *
 * Return the length of the shortest subarray to remove.
 *
 * A subarray is a contiguous subsequence of the array.
 *
 * ! 1 <= arr.length <= 10^5
 * ! 0 <= arr[i] <= 10^9
 */

class Solution
{
public:
    int findLengthOfShortestSubarray(std::vector<int>& arr)
    {
        // similar to LC 2972
        const int n = arr.size();
        // find the largest i such that arr[0:i] is non-decreasing
        int i = 0;
        while (i + 1 < n && arr[i] <= arr[i + 1]) {
            i++;
        }
        // if i == n - 1, the input array is already non-decreasing
        if (i == n - 1)
            return 0;

        // we can remove nums[i+1:n-1] to make the array non-decreasing
        int result = n - i - 1;
        // or we can fix nums[j] as the last element of the modified array
        // find the largest i such that nums[0:i] is non-decreasing and nums[i] <= nums[j]
        // then we can remove nums[i+1:n-1] to make the array non-decreasing
        for (int j = n - 1; j > 0; --j) {
            while (i >= 0 && arr[i] > arr[j]) {
                i--;
            }
            result = std::min(result, j - i - 1);
            if (arr[j] < arr[j - 1])
                break;
        }
        return result;
    }
};