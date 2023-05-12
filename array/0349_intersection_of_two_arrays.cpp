#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Given two integer arrays "nums1" and "nums2", return an array of their intersection. Each element
 * in the result must be unique and you may return the result in any order.
 */

class Solution
{
public:
    std::vector<int> intersection(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        if (nums1.empty() || nums2.empty())
            return {};

        std::vector<int> result;
        // approach 1: hash set
        std::unordered_set<int> set(nums1.begin(), nums1.end());
        for (const auto& i : nums2) {
            if (set.erase(i)) {
                result.push_back(i);
            }
        }
        // approach 2: hash map
        // std::unordered_map<int, int> map;
        // for (const auto& i : nums1) {
        //     map[i] = 1;
        // }
        // for (const auto& i : nums2) {
        //     if (--map[i] == 0) {
        //         result.push_back(i);
        //     }
        // }
        return result;
    }
};