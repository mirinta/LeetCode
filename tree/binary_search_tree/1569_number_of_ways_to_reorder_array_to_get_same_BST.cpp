#include <vector>

/**
 * Given an array nums that represents a permutation of integers from 1 to n. We are going to
 * construct a binary search tree (BST) by inserting the elements of nums in order into an initially
 * empty BST. Find the number of different ways to reorder nums so that the constructed BST is
 * identical to that formed from the original array nums.
 *
 * - For example, given nums = [2,1,3], we will have 2 as the root, 1 as a left child, and 3 as a
 * right child. The array [2,3,1] also yields the same BST but [3,2,1] yields a different BST.
 *
 * Return the number of ways to reorder nums such that the BST formed is identical to the original
 * BST formed from nums.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= nums.length
 * ! All integers in nums are distinct.
 *
 * Example:
 * Input: nums = [3,4,5,1,2]
 * Output: 5
 * Explanation: The following 5 arrays will yield the same BST:
 * [3,1,2,4,5]
 * [3,1,4,2,5]
 * [3,1,4,5,2]
 * [3,4,1,2,5]
 * [3,4,1,5,2]
 */

class Solution
{
public:
    int numOfWays(const std::vector<int>& nums)
    {
        memo.clear();
        const auto m = nums.size();
        memo.resize(m + 1, std::vector<long long>(m + 1, -1));
        return solve(nums) - 1; // "nums" itself is not taken into account
    }

private:
    static constexpr int kMod = 1e9 + 7;
    long long solve(const std::vector<int>& nodes)
    {
        if (nodes.size() < 3)
            return 1;

        std::vector<int> leftNodes;
        std::vector<int> rightNodes;
        for (size_t i = 1; i < nodes.size(); ++i) {
            if (nodes[i] > nodes[0]) {
                leftNodes.push_back(nodes[i]);
            } else {
                rightNodes.push_back(nodes[i]);
            }
        }
        const long long waysOfLeft = solve(leftNodes);
        const long long waysOfRight = solve(rightNodes);
        // 3 4 5 1 2
        // - root node is 3
        // - left subtree is [4,5]
        // - right subtree is [1,2]
        // - 3[][][][], choose 2 brackets to fill in nodes of left subtree, #ways = C(4,2)
        const long long combinations = getCombo(nodes.size() - 1, leftNodes.size());
        return ((waysOfLeft * waysOfRight) % kMod * combinations) % kMod;
    }

    std::vector<std::vector<long long>> memo;
    long long getCombo(int m, int n)
    {
        // C(m,n) = C(m-1,n) + C(m-1,n-1)
        if (n == 0)
            return 1;

        if (n == 1)
            return m;

        if (memo[m][n] != -1)
            return memo[m][n];

        if (n > m - n)
            return getCombo(m, m - n);

        memo[m][n] = (getCombo(m - 1, n) + getCombo(m - 1, n - 1)) % kMod;
        return memo[m][n];
    }
};