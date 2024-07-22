#include <vector>

/**
 * There is a circle of red and blue tiles. You are given an array of integers colors and an integer
 * k. The color of tile i is represented by colors[i]:
 *
 * - colors[i] == 0 means that tile i is red.
 *
 * - colors[i] == 1 means that tile i is blue.
 *
 * An alternating group is every k contiguous tiles in the circle with alternating colors (each tile
 * in the group except the first and last one has a different color from its left and right tiles).
 *
 * Return the number of alternating groups.
 *
 * Note that since colors represents a circle, the first and the last tiles are considered to be
 * next to each other.
 *
 * ! 3 <= colors.length <= 10^5
 * ! 0 <= colors[i] <= 1
 * ! 3 <= k <= colors.length
 */

class Solution
{
public:
    int numberOfAlternatingGroups(std::vector<int>& colors, int k)
    {
        // count[i] = max num of alternating colors of nums[0:i] ending at nums[i]
        const int n = colors.size();
        std::vector<int> count(n, 0);
        for (int i = 0; i < 2 * n; ++i) {
            const int curr = i % n;
            const int prev = (i - 1 + n) % n;
            if (colors[curr] != colors[prev]) {
                count[curr] = count[prev] + 1;
            } else {
                count[curr] = 0;
            }
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += count[i] >= k - 1;
        }
        return result;
    }
};