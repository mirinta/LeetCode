#include <string>

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
    int sumNumbers(TreeNode* root) { return approach2(root); }

private:
    int approach2(TreeNode* root)
    {
        int result = 0;
        traverse(result, 0, root);
        return result;
    }

    void traverse(int& result, int num, TreeNode* node)
    {
        if (!node)
            return;

        num = num * 10 + node->val;
        if (!node->left && !node->right) {
            result += num;
        }
        traverse(result, num, node->left);
        traverse(result, num, node->right);
    }

    int approach1(TreeNode* root)
    {
        std::string path;
        int result = 0;
        backtrack(path, result, root);
        return result;
    }

    void backtrack(std::string& path, int& result, TreeNode* node)
    {
        if (!node)
            return;

        path.push_back(node->val + '0');
        if (!node->left && !node->right) {
            result += std::stoi(path);
        }
        backtrack(path, result, node->left);
        backtrack(path, result, node->right);
        path.pop_back();
    }
};