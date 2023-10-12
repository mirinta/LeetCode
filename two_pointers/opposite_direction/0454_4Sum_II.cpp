#include <unordered_map>
#include <vector>

/**
 * Given four integer arrays "nums1", "nums2", "nums3" and "nums4" all of length "n", return the
 * number of tuples (i, j, k, l) such that:
 *
 * - 0 <= i, j, k, l < n
 *
 * - nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
 */

class Solution
{
public:
    int fourSumCount(const std::vector<int>& nums1, const std::vector<int>& nums2,
                     const std::vector<int>& nums3, const std::vector<int>& nums4)
    {
        int result = 0;
        std::unordered_map<int, int> map; // key = sum in nums1 and nums2, value = frequency
        for (const auto& i : nums1) {
            for (const auto& j : nums2) {
                map[i + j]++;
            }
        }
        for (const auto& k : nums3) {
            for (const auto& l : nums4) {
                const auto target = -k - l;
                if (map.count(target)) {
                    result += map[target];
                }
            }
        }
        return result;
    }
};
