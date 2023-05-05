#include <vector>

/**
 * You are given two integer arrays "nums1" and "nums2", sorted in non-decreasing order, and two
 * integers "m" and "n", representing the number of elements in nums1 and nums2 respectively.
 *
 * Merge nums1 and nums2 into a single array sorted in non-decreasing order.
 *
 * The final sorted array should not be returned by the function, but instead be stored inside the
 * array nums1. To accommodate this, nums1 has a length of m + n, where the first m elements denote
 * the elements that should be merged, and the last n elements are set to 0 and should be ignored.
 * nums2 has a length of n.
 */

class Solution
{
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n)
    {
        for (int k = m + n - 1, i = m - 1, j = n - 1; k >= 0; --k) {
            if (i < 0 && j < 0)
                break;

            if (i >= 0 && j < 0) {
                nums1[k] = nums1[i--];
                continue;
            }
            if (i < 0 && j >= 0) {
                nums1[k] = nums2[j--];
                continue;
            }
            if (nums2[j] > nums1[i]) {
                nums1[k] = nums2[j--];
            } else {
                nums1[k] = nums1[i--];
            }
        }
    }
};