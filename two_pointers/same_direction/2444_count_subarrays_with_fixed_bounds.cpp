#include <vector>

/**
 * You are given an integer array nums and two integers minK and maxK.
 *
 * A fixed-bound subarray of nums is a subarray that satisfies the following conditions:
 *
 * - The minimum value in the subarray is equal to minK.
 *
 * - The maximum value in the subarray is equal to maxK.
 *
 * Return the number of fixed-bound subarrays.
 *
 * A subarray is a contiguous part of an array.
 *
 * ! 2 <= nums.length <= 10^5
 * ! 1 <= nums[i], minK, maxK <= 10^6
 */

class Solution
{
public:
    long long countSubarrays(std::vector<int>& nums, int minK, int maxK)
    {
        // use elements < minK or > maxK as boundaries
        // ... X X+1 ... lastMin ... lastMax ... i
        //     ^
        //     lastBoundary
        //
        // num of valid subarrays ending at nums[i]:
        // nums[X+1:i], nums[X+2:i], ..., nums[lastMin:i]
        // thus, count = std::max(0, std::min(lastMin, lastMax) - lastBoundary)
        const int n = nums.size();
        long long result = 0;
        int lastMin = -1;
        int lastMax = -1;
        int lastBoundary = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] < minK || nums[i] > maxK) {
                lastBoundary = i;
                continue;
            }
            if (nums[i] == minK) {
                lastMin = i;
            }
            if (nums[i] == maxK) {
                lastMax = i;
            }
            result += std::max(0, std::min(lastMin, lastMax) - lastBoundary);
        }
        return result;
    }
};