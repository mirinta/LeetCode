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
 * Given the "root" of a BST, return the minimum absolute difference between the values of two
 * different nodes in the tree.
 *
 * ! This question is the same as LC.783.
 *
 * ! The number of nodes in the tree is in the range [2, 10^4].
 * ! 0 <= Node.val <= 10^5
 */

class Solution
{
public:
    int getMinimumDifference(TreeNode* root)
    {
        std::vector<int> inorder;
        dfs(inorder, root);
        int result = INT_MAX;
        for (int i = 1; i < inorder.size(); ++i) {
            result = std::min(result, inorder[i] - inorder[i - 1]);
        }
        return result;
    }

private:
    void dfs(std::vector<int>& inorder, TreeNode* root)
    {
        if (!root)
            return;

        dfs(inorder, root->left);
        inorder.push_back(root->val);
        dfs(inorder, root->right);
    }
};
