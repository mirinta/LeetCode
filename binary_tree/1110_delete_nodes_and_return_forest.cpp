#include <unordered_set>
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
 * Given the root of a binary tree, each node in the tree has a distinct value.
 *
 * After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union
 * of trees).
 *
 * Return the roots of the trees in the remaining forest. You may return the result in any order.
 *
 * ! The number of nodes in the given tree is at most 1000.
 * ! Each node has a distinct value between 1 and 1000.
 * ! to_delete.length <= 1000
 * ! to_delete contains distinct values between 1 and 1000.
 */

class Solution
{
public:
    std::vector<TreeNode*> delNodes(TreeNode* root, std::vector<int>& to_delete)
    {
        if (!root)
            return {};

        std::unordered_set<int> toDelete(to_delete.begin(), to_delete.end());
        std::vector<TreeNode*> result;
        if (dfs(result, toDelete, root)) {
            result.push_back(root);
        }
        return result;
    }

private:
    TreeNode* dfs(std::vector<TreeNode*>& result, std::unordered_set<int>& toDelete, TreeNode* node)
    {
        if (!node)
            return nullptr;

        // if this node is deleted, return nullptr
        // otherwise, update its left and right subtrees, and check:
        // if the left subtree is not deleted, add it to the forest
        // if the right subtree is not deleted, add it to the forest
        node->left = dfs(result, toDelete, node->left);
        node->right = dfs(result, toDelete, node->right);
        if (!toDelete.count(node->val))
            return node;

        if (node->left) {
            result.push_back(node->left);
        }
        if (node->right) {
            result.push_back(node->right);
        }
        return nullptr;
    }
};
