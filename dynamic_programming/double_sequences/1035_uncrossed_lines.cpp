#include <vector>

/**
 * You are given two integer arrays "nums1" and "nums2". We write the integers of "nums1" and
 * "nums2" (in the order they are given) on two separated horizontal lines.
 *
 * We may draw connecting lines: a straight line connecting two numbers "nums1[i]" and "nums2[j]"
 * such that:
 *
 * - nums1[i] == nums2[j], and
 *
 * - the line we draw does not intersect any ohter connecting (non-horizontal) line.
 *
 * Note that a connecting line cannot intersect even at the endpoints (i.e., each number can only
 * belong the one connecting line).
 *
 * Return the maximum number of connecting lines we can draw in this way.
 */

class Solution
{
public:
    // nums1 = [1, 4, 2], nums2 = [1, 2, 4]
    // two uncrossed lines: [1-1, 4-4]
    // [1, 4] is the longest common subsequence of nums1 and nums2!
    // see LC 1143
    int maxUncrossedLines(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const auto m = nums1.size();
        const auto n = nums2.size();
        std::vector<std::vector<int>> table(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    table[i][j] = 1 + table[i - 1][j - 1];
                } else {
                    table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
                }
            }
        }
        return table[m][n];
    }
};