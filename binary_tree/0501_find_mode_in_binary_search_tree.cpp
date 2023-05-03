#include <vector>

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
 * Given the "root" of a binary search tree with duplicates, return all the mode(s) (i.e., the most
 * frequently occurred element in it).
 *
 * If the tree has more than one mode, return them in any order.
 *
 * Assume a BST is defined as follows:
 *
 * - The left subtree of a node contains only nodes with keys less than or equal to the node's key.
 *
 * - The right subtree of a node contains only nodes with keys greater than or equal to the node's
 * key.
 *
 * - Both the left and right subtrees must also be binary search trees.
 *
 * ! Could you do that without using any extra space?
 * ! Assume that the implicit stack space incurred due to recursion does not count.
 */

class Solution
{
public:
    std::vector<int> findMode(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> result;
        traverse(root, result);
        return result;
    }

private:
    int count = 0; // record frequency of current value
    int maxFreq = 0;
    TreeNode* prev = nullptr; // record previous node
    void traverse(TreeNode* node, std::vector<int>& result)
    {
        if (!node)
            return;

        traverse(node->left, result);
        if (prev && prev->val == node->val) {
            count++;
        } else {
            count = 0;
        }
        prev = node;
        if (count == maxFreq) {
            result.push_back(node->val);
        }
        if (count > maxFreq) {
            maxFreq = count;
            result.clear();
            result.push_back(node->val);
        }
        traverse(node->right, result);
    }
};