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
 * You are given the root of a binary tree containing digits from 0 to 9 only.
 *
 * Each root-to-leaf path in the tree represents a number.
 *
 * - For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
 *
 * Return the total sum of all root-to-leaf numbers. Test cases are generated so that the answer
 * will fit in a 32-bit integer.
 *
 * A leaf node is a node with no children.
 *
 * ! The number of nodes in the tree is in the range [1, 1000].
 * ! 0 <= Node.val <= 9
 * ! The depth of the tree will not exceed 10.
 */

class Solution
{
public:
    int sumNumbers(TreeNode* root)
    {
        if (!root)
            return 0;

        int result = 0;
        dfs(result, 0, root);
        return result;
    }

private:
    void dfs(int& result, int num, TreeNode* root)
    {
        if (!root)
            return;

        num = num * 10 + root->val;
        if (!root->left && !root->right) {
            result += num;
        }
        dfs(result, num, root->left);
        dfs(result, num, root->right);
    }
};
