#include <utility>

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * The thief has found himself a new place for this thievery again. There is only one entrance to
 * this area, called "root".
 *
 * Besides the "root", each house has one and only one parent house. After a tour, the smart thief
 * realized that all houses in this place from a binary tree. It will automatically contact the
 * police if two directly-linked houses were broken into on the same night.
 *
 * Given the "root" of the binary tree, return the maximum amount of money the thief can rob without
 * altering the police.
 *
 * ! 0 <= Node.val <= 104
 */

class Solution
{
public:
    int rob(TreeNode* root)
    {
        if (!root)
            return 0;

        const auto [notRobTheFirst, robTheFirst] = dp(root);
        return std::max(notRobTheFirst, robTheFirst);
    }

private:
    // <v1, v2>
    // - v1 = max amount of money, start from the current house and the current house is not robbed
    // - v2 = max amount of money, start from the current house and the current house is robbed
    std::pair<int, int> dp(TreeNode* root)
    {
        if (!root)
            return {0, 0};

        // solve subproblems:
        const auto [notRobLeft, robLeft] = dp(root->left);
        const auto [notRobRight, robRight] = dp(root->right);
        // make choice: rob or not rob the current house
        // - if rob, both left and right house can't be robbed
        const auto rob = root->val + notRobLeft + notRobRight;
        const auto notRob = std::max(notRobLeft, robLeft) + std::max(notRobRight, robRight);
        return {notRob, rob};
    }
};