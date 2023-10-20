#include <vector>

/**
 * If the depth of a tree is smaller than 5, then this tree can be represented by an array of
 * three-digit integers. For each integer in this array:
 *
 * - The hundreds digit represents the depth d of this node where 1 <= d <= 4.
 *
 * - The tens digit represents the position p of this node in the level it belongs to where 1 <= p
 * <= 8. The position is the same as that in a full binary tree.
 *
 * - The units digit represents the value v of this node where 0 <= v <= 9.
 *
 * Given an array of ascending three-digit integers nums representing a binary tree with a depth
 * smaller than 5, return the sum of all paths from the root towards the leaves.
 *
 * It is guaranteed that the given array represents a valid connected binary tree.
 *
 * ! 1 <= nums.length <= 15
 * ! 110 <= nums[i] <= 489
 * ! nums represents a valid binary tree with depth less than 5.
 */

class Solution
{
public:
    int pathSum(std::vector<int>& nums)
    {
        /**
         *       3 index=0
         *      / \
         *     5   1
         * index=0 index=1
         */
        // data[i][j] is the sum along the path from root to node(i,j)
        constexpr int m = 5; // the depth is in the range [1, 4]
        constexpr int n = 8;
        std::vector<std::vector<int>> data(m, std::vector<int>(n, 0));
        for (const auto& num : nums) {
            const int depth = num / 100;
            const int index = (num / 10) % 10 - 1; // 0-indexed
            const int val = num % 10;
            data[depth][index] = val + data[depth - 1][index / 2];
        }
        int result = 0;
        // find all the leaves and sum their values
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == m - 1 ||
                    (data[i][j] != 0 && data[i + 1][2 * j] == 0 && data[i + 1][2 * j + 1] == 0)) {
                    result += data[i][j];
                }
            }
        }
        return result;
    }
};
