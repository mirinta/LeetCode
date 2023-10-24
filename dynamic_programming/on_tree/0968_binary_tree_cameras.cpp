#include <tuple>

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
 * You are given the root of a binary tree. We install cameras on the tree nodes where each camera
 * at a node can monitor its parent, itself, and its immediate children.
 *
 * Return the minimum number of cameras needed to monitor all nodes of the tree.
 *
 * ! The number of nodes in the tree is in the range [1, 1000].
 * ! Node.val == 0
 */

class Solution
{
public:
    int minCameraCover(TreeNode* root)
    {
        const auto [install, coveredByParent, coveredByChild] = dfs(root);
        return std::min(install, coveredByChild);
    }

    /**
     *      parent
     *        |
     *      current
     *       /  \
     * child1    child2
     *
     * return[0] = min num of cameras if install camera on current, current is covered by itself
     * return[1] = min num of cameras if no camera on current, but current is covered by its parent
     * return[2] = min num of cameras if no camera on current, but current is covered by one of its
     * children
     */
    std::tuple<int, int, int> dfs(TreeNode* current)
    {
        if (!current)
            return {INT_MAX / 2, 0, 0};

        const auto [left0, left1, left2] = dfs(current->left);
        const auto [right0, right1, right2] = dfs(current->right);
        // case1: install camera on current node
        // - left/right child can be any status
        const int install =
            1 + std::min({left0, left1, left2}) + std::min({right0, right1, right2});
        // case2: no camera on current node, it is covered by its parent
        // - left/right child can have camera or covered by its children
        const int coveredByParent = std::min(left0, left2) + std::min(right0, right2);
        // case3: no camera on current node, it is covered by one of its children
        // - left child has camera, right child has no camera and is covered by its children
        // - right child has camera, left child has no camera and is covered by its children
        // - both left and right child have camera
        const int coveredByChild = std::min({left0 + right0, left0 + right2, left2 + right0});
        return {install, coveredByParent, coveredByChild};
    }
};
