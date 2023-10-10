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
 * Given a binary tree root, a node X in the tree is named good if in the path from root to X there
 * are no nodes with a value greater than X.
 *
 * Return the number of good nodes in the binary tree.
 *
 * ! The number of nodes in the binary tree is in the range [1, 10^5].
 * ! Each node's value is between [-10^4, 10^4].
 */

class Solution
{
public:
    int goodNodes(TreeNode* root)
    {
        if (!root)
            return 0;

        int result = 0;
        dfs(result, INT_MIN, root);
        return result;
    }

private:
    void dfs(int& result, int prevMax, TreeNode* node)
    {
        if (!node)
            return;

        const int currentMax = std::max(node->val, prevMax);
        if (node->val == currentMax) {
            result++;
        }
        dfs(result, currentMax, node->left);
        dfs(result, currentMax, node->right);
    }
};
