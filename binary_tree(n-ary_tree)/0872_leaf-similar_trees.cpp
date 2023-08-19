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
 * Consider all the leaves of a binary tree, from left to right order, the values of those leaves
 * form a leaf value sequence.
 *
 * Two binary trees are considered leaf-similar if their leaf value sequence is the same.
 *
 * Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.
 *
 * ! The number of nodes in each tree will be in the range [1, 200].
 * ! Both of the given trees will have values in the range [0, 200].
 */

class Solution
{
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2)
    {
        std::vector<int> nodes1;
        traverse(nodes1, root1);
        std::vector<int> nodes2;
        traverse(nodes2, root2);
        return nodes1 == nodes2;
    }

private:
    void traverse(std::vector<int>& nodes, TreeNode* node)
    {
        if (!node)
            return;

        if (!node->left && !node->right) {
            nodes.push_back(node->val);
            return;
        }
        traverse(nodes, node->left);
        traverse(nodes, node->right);
    }
};