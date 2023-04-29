#include <unordered_map>
#include <vector>

/**
 * Given two integer arrays "nums1" and "nums2", return an array of their intersection. Each element
 * in the result must appear as many times as it shows in both arrays and you may return the result
 * in any order.
 */

class Solution
{
public:
    std::vector<int> intersect(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        if (nums1.empty() || nums2.empty())
            return {};

        std::unordered_map<int, int> freq;
        for (const auto& i : nums1) {
            freq[i]++;
        }
        std::vector<int> result;
        for (const auto& i : nums2) {
            if (--freq[i] >= 0) {
                result.push_back(i);
            }
        }
        return result;
    }
};