#include <algorithm>
#include <vector>

/**
 * A permutation of an array of integers is an arrangement of its members into a sequence or linear
 * order.
 *
 * - For example, for arr = [1,2,3], the following are all the permutations of arr: [1,2,3],
 * [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
 *
 * The next permutation of an array of integers is the next lexicographically greater permutation of
 * its integer. More formally, if all the permutations of the array are sorted in one container
 * according to their lexicographical order, then the next permutation of that array is the
 * permutation that follows it in the sorted container. If such arrangement is not possible, the
 * array must be rearranged as the lowest possible order (i.e., sorted in ascending order).
 *
 * - For example, the next permutation of arr = [1,2,3] is [1,3,2].
 *
 * - Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
 *
 * - While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a
 * lexicographical larger rearrangement.
 *
 * Given an array of integers nums, find the next permutation of nums.
 *
 * The replacement must be in place and use only constant extra memory.
 *
 * ! 1 <= nums.length <= 100
 * ! 0 <= nums[i] <= 100
 */

class Solution
{
public:
    void nextPermutation(std::vector<int>& nums)
    {
        // our goal is to find the next greater number
        // corner case:
        // if the given sequence is already sorted in non-increasing order,
        // it is already the largest number, so we just return the smallest number
        // e.g., given 4 3 2 1, and return 1 2 3 4
        // normal case:
        // 4 1 5 3 2
        //   ^ |<->|
        // replace 1 with the the smallest number in [5,3,2] that is greater than 1 => 4 2 5 3 1
        // sort [5 3 1] in non-decreasing order => 4 2 1 3 5, this is the final answer
        if (nums.size() == 1)
            return;

        // X X i-1 i X X X N-1
        //         |<------->|, non-decreasing from right to left
        const int n = nums.size();
        int i = n - 1;
        while (i >= 1 && nums[i] <= nums[i - 1]) {
            i--;
        }
        if (i == 0) {
            // it is the largest permutation
            std::sort(nums.begin(), nums.end());
            return;
        }
        if (i == n - 1) {
            // it is the smallest permutation
            std::swap(nums[n - 1], nums[n - 2]);
            return;
        }
        const int val = nums[i - 1]; // this is the number we want to replace
        auto iter = std::upper_bound(nums.rbegin(), std::next(nums.rbegin(), n - i), val);
        std::swap(nums[i - 1], *iter);
        std::sort(std::next(nums.begin(), i), nums.end());
    }
};