#include <vector>

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
 * Given the "root" of a binary tree and an integer "targetSum", return all root-to-leaf paths where
 * the sum of the node values in the path equals "targetSum". Each path should be returned as a list
 * of the node values, not node references.
 *
 * A root-to-leaf path is a path starting from the root and ending at any leaf node. A leaf node is
 * a node with no children.
 *
 * ! The number of nodes in the tree is in the range [0, 5000].
 * ! -1000 <= Node.val <= 1000
 * ! -1000 <= targetSum <= 1000
 */

class Solution
{
public:
    std::vector<std::vector<int>> pathSum(TreeNode* root, int targetSum)
    {
        if (!root)
            return {};

        std::vector<std::vector<int>> result;
        std::vector<int> path;
        backtrack(result, path, targetSum, root);
        return result;
    }

private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& path, int targetSum,
                   TreeNode* root)
    {
        if (!root)
            return;

        if (root->val == targetSum && !root->left && !root->right) {
            result.push_back(path);
            result.back().push_back(root->val);
            return;
        }
        path.push_back(root->val);
        backtrack(result, path, targetSum - root->val, root->left);
        backtrack(result, path, targetSum - root->val, root->right);
        path.pop_back();
    }
};