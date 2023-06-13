#include <utility>

/**
 Definition for a binary tree node.
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
 * A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence
 * has an edge connecting them. A node can only appear in the sequence at most once. Note that the
 * path does not need to pass through the root.
 *
 * The path sum of a path is the sum of the node's values in the path.
 *
 * Given the "root" of a binary tree, return the maximum path sum of any non-empty path.
 *
 * ! The number of nodes in the tree is in the range [1, 3 * 10^4].
 * ! -1000 <= Node.val <= 1000
 */

class Solution
{
public:
    int maxPathSum(TreeNode* root)
    {
        if (!root)
            return 0;

        int result = INT_MIN;
        traverse(result, root);
        return result;
    }

private:
    // max sum of one side path  (either left side or right side)
    int traverse(int& result, TreeNode* node)
    {
        if (!node)
            return 0;

        const auto left = traverse(result, node->left);
        const auto right = traverse(result, node->right);
        result = std::max(result, node->val + std::max(0, left) + std::max(0, right));
        return std::max({0, left, right}) + node->val;
    }
};