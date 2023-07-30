#include <vector>

/**
 * Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the
two sorted arrays.
 *
 * The overall run time complexity should be O(log (m+n)).
 *
 * ! nums1.length == m
 * ! nums2.length == n
 * ! 0 <= m <= 1000
 * ! 0 <= n <= 1000
 * ! 1 <= m + n <= 2000
 * ! -10^6 <= nums1[i], nums2[i] <= 10^6
 */

class Solution
{
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        if (nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);

        const int m = nums1.size();
        const int n = nums2.size();
        // cut nums1 into two parts:
        // choose a cutting position i, where 0 <= i <= m
        // [0 ... i-1] [i ... m-1]
        // |   LEFT  | |  RIGHT  |
        // if i = 0, then LEFT = [] and RIGHT = num1
        // if i = m, then LEFT = nums1 and RIGHT = []
        int left = 0;
        int right = m;
        while (left <= right) {
            const int cut1 = left + (right - left) / 2;
            const int cut2 = (m + n + 1) / 2 - cut1;
            const int maxLeft1 = cut1 == 0 ? INT_MIN : nums1[cut1 - 1];
            const int minRight1 = cut1 == m ? INT_MAX : nums1[cut1];
            const int maxLeft2 = cut2 == 0 ? INT_MIN : nums2[cut2 - 1];
            const int minRight2 = cut2 == n ? INT_MAX : nums2[cut2];
            if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
                if ((m + n) % 2 == 0)
                    return (std::max(maxLeft1, maxLeft2) + std::min(minRight1, minRight2)) * 0.5;

                return std::max(maxLeft1, maxLeft2);
            } else if (maxLeft1 > minRight2) {
                right = cut1 - 1;
            } else {
                left = cut1 + 1;
            }
        }
        return 0;
    }

private:
    // merge with space optimization, time O(m+n), space O(1)
    double approach2(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        // if length is odd, we want (m+n)/2
        // if length is even, we want (m+n)/2 and (m+n)/2-1
        int i = 0;
        int j = 0;
        auto getMin = [&]() -> double {
            if (i == m)
                return nums2[j++];
            if (j == n)
                return nums1[i++];
            if (nums2[j] < nums1[i])
                return nums2[j++];
            return nums1[i++];
        };
        if ((m + n) % 2 == 0) {
            for (int k = 0; k < (m + n) / 2 - 1; ++k) {
                getMin();
            }
            return (getMin() + getMin()) * 0.5;
        }
        for (int k = 0; k < (m + n) / 2; ++k) {
            getMin();
        }
        return getMin();
    }

    // merge, time O(m+n), space O(m+n)
    int approach1(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        std::vector<int> merge(m + n, 0);
        for (int k = 0, i = 0, j = 0; k < merge.size(); ++k) {
            if (i == m) {
                merge[k] = nums2[j++];
                continue;
            }
            if (j == n) {
                merge[k] = nums1[i++];
                continue;
            }
            if (nums2[j] < nums1[i]) {
                merge[k] = nums2[j++];
            } else {
                merge[k] = nums1[i++];
            }
        }
        const int mid = (m + n) / 2;
        return (m + n) % 2 == 1 ? merge[mid] : (merge[mid] + merge[mid - 1]) * 1.0 / 2;
    }
};