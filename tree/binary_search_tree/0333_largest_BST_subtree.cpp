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
 * Given the root of a binary tree, find the largest subtree, which is also a Binary Search Tree
 * (BST), where the largest means subtree has the largest number of nodes.
 *
 * A Binary Search Tree (BST) is a tree in which all the nodes follow the below-mentioned
 * properties:
 *
 * - The left subtree values are less than the value of their parent (root) node's value.
 *
 * - The right subtree values are greater than the value of their parent (root) node's value.
 *
 * Note: A subtree must include all of its descendants.
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! -10^4 <= Node.val <= 10^4
 */

class Solution
{
public:
    int largestBSTSubtree(TreeNode* root)
    {
        int result = 0;
        dfs(result, root);
        return result;
    }

private:
    // return[0] = min value of this tree
    // return[1] = max value of this tree
    // return[2] = num of nodes of this tree
    // use post-order traversal to check whether root is a BST
    // if root is a BST, then leftMax < root->val < rightMin
    std::tuple<int, int, int> dfs(int& result, TreeNode* root)
    {
        if (!root)
            return {INT_MAX, INT_MIN, 0};

        const auto [leftMin, leftMax, leftCount] = dfs(result, root->left);
        const auto [rightMin, rightMax, rightCount] = dfs(result, root->right);
        const int count = 1 + leftCount + rightCount;
        if (root->val <= leftMax || root->val >= rightMin)
            return {INT_MIN, INT_MAX, count};

        result = std::max(result, count);
        // if root->left is null, leftMin = INT_MAX
        // if root->right is null, rightMax = INT_MIN
        // thus, we use min and max functions to ensure the returned range is valid
        return {std::min(root->val, leftMin), std::max(root->val, rightMax), count};
    }
};
