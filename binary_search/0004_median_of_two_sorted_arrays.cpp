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
    // time O(log(min(M,N))), space O(1)
    double approach3(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        if (nums1.size() > nums2.size())
            return approach3(nums2, nums1);

        const int m = nums1.size();
        const int n = nums2.size();
        // divide nums1 into two parts: [...LEFT_MAX_1][RIGHT_MIN_1...]
        // divide nums2 into two parts: [...LEFT_MAX_2][RIGHT_MIN_2...]
        // make sure LEFT1.size + LEFT2.size = (m + n + 1) / 2
        // the expected array after merging: [LEFT_1 and LEFT_2][RIGHT_1 and RIGHT_2]
        int lo = 0;
        int hi = m;
        while (lo <= hi) {
            const int cut1 = lo + (hi - lo) / 2;
            const int cut2 = (m + n + 1) / 2 - cut1;
            const int leftMax1 = cut1 == 0 ? INT_MIN : nums1[cut1 - 1];
            const int rightMin1 = cut1 == m ? INT_MAX : nums1[cut1];
            const int leftMax2 = cut2 == 0 ? INT_MIN : nums2[cut2 - 1];
            const int rightMin2 = cut2 == n ? INT_MAX : nums2[cut2];
            if (leftMax1 <= rightMin2 && leftMax2 <= rightMin1) {
                if ((m + n) % 2)
                    return std::max(leftMax1, leftMax2);

                return 0.5 * (std::max(leftMax1, leftMax2) + std::min(rightMin1, rightMin2));
            }
            if (leftMax1 > rightMin2) {
                hi = cut1 - 1;
            } else {
                lo = cut1 + 1;
            }
        }
        return INT_MAX;
    }

    // time O(M+N), space O(1)
    double approach2(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        int i = 0;
        int j = 0;
        auto nextSmaller = [&]() {
            if (i == m && j == n)
                return INT_MAX;
            if (i == m)
                return nums2[j++];
            if (j == n)
                return nums1[i++];
            if (nums1[i] > nums2[j])
                return nums2[j++];
            return nums1[i++];
        };
        int current = 0;
        for (int k = 0, mid = (m + n) / 2; k < mid; ++k) {
            current = nextSmaller();
        }
        if ((m + n) % 2)
            return nextSmaller();

        return 0.5 * (current + nextSmaller());
    }

    // time O(M+N), space O(M+N)
    double approach1(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        std::vector<int> aux(m + n);
        for (int i = 0, j = 0, k = 0; k < aux.size(); ++k) {
            if (i == m) {
                aux[k] = nums2[j++];
                continue;
            }
            if (j == n) {
                aux[k] = nums1[i++];
                continue;
            }
            if (nums1[i] > nums2[j]) {
                aux[k] = nums2[j++];
            } else {
                aux[k] = nums1[i++];
            }
        }
        const bool isOdd = (m + n) % 2;
        const int mid = (m + n) / 2;
        if (isOdd)
            return aux[mid];

        return 0.5 * (aux[mid] + aux[mid - 1]);
    }
};