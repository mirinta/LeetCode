#include <vector>

/**
 * Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the
 * two sorted arrays.
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
        return approach3(nums1, nums2);
    }

private:
    // binary search, time O(log(min(M, N))), space O(1)
    double approach3(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        if (nums1.size() > nums2.size())
            return approach3(nums2, nums1);

        const int m = nums1.size();
        const int n = nums2.size();
        const int totalLength = m + n;
        int lo = 0;
        int hi = m;
        while (lo <= hi) {
            // cut nums1 at cut1
            // 0 ... cut1-1 cut1 ... m-1
            // |<--LEFT-->| |<-RIGHT-->|
            // - if i = 0, LEFT = {}, RIGHT = {0...m-1}
            // - if i = m, LEFT = {0...m-1}, RIGHT = {}
            // - LEFT_ELEMS_1 = i
            const int cut1 = lo + (hi - lo) / 2;
            // cut nums2 at cut2
            // odd length: [0 1 2][3 4], cutting position=3=(5+1)/2
            // even length: [0 1][2 3], cutting position=2=(4+1)/2
            const int cut2 = (totalLength + 1) / 2 - cut1;
            // nums1 => [...MaxLeft1] | [MinRight1...]
            // nums2 => [...MaxLeft2] | [MinRight2...]
            const int maxLeft1 = cut1 == 0 ? INT_MIN : nums1[cut1 - 1];
            const int minRight1 = cut1 == m ? INT_MAX : nums1[cut1];
            const int maxLeft2 = cut2 == 0 ? INT_MIN : nums2[cut2 - 1];
            const int minRight2 = cut2 == n ? INT_MAX : nums2[cut2];
            if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
                if (totalLength % 2 == 0)
                    return (std::max(maxLeft1, maxLeft2) + std::min(minRight1, minRight2)) * 0.5;

                return std::max(maxLeft1, maxLeft2);
            }
            if (maxLeft1 > minRight2) {
                hi = cut1 - 1;
            } else {
                lo = cut1 + 1;
            }
        }
        return 0;
    }

    // merge with space optimization, time O(M+N), space O(1)
    double approach2(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        int i = 0;
        int j = 0;
        auto nextMin = [&]() {
            const int m = nums1.size();
            const int n = nums2.size();
            if (i == m && j < n)
                return nums2[j++];

            if (j == n && i < m)
                return nums1[i++];

            return nums1[i] < nums2[j] ? nums1[i++] : nums2[j++];
        };
        if ((m + n) % 2 == 0) {
            for (int k = 0; k < (m + n) / 2 - 1; ++k) {
                nextMin();
            }
            return (nextMin() + nextMin()) * 0.5;
        }
        for (int k = 0; k < (m + n) / 2; ++k) {
            nextMin();
        }
        return nextMin();
    }

    // merge, time O(M+N), space O(M+N)
    double approach1(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        const int totalLength = m + n;
        std::vector<int> vec(totalLength, 0);
        for (int k = 0, i = 0, j = 0; k < vec.size(); ++k) {
            if (i == m) {
                vec[k] = nums2[j++];
            } else if (j == n) {
                vec[k] = nums1[i++];
            } else if (nums1[i] < nums2[j]) {
                vec[k] = nums1[i++];
            } else {
                vec[k] = nums2[j++];
            }
        }
        if (totalLength % 2 == 0)
            return (vec[totalLength / 2 - 1] + vec[totalLength / 2]) * 0.5;

        return vec[totalLength / 2];
    }
};
