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
        dfs(result, toDelete, root, true);
        return result;
    }

private:
    TreeNode* dfs(std::vector<TreeNode*>& result, std::unordered_set<int>& toDelete, TreeNode* node,
                  bool isRoot)
    {
        if (!node)
            return nullptr;

        // if this node is a root node (i.e, has no parent node),
        // and it is not going to be deleted, then we add it to the result
        const bool deleted = toDelete.count(node->val);
        if (isRoot && !deleted) {
            result.push_back(node);
        }
        // if this node needs to be deleted,
        // then both node->left and node->right will become two separate trees
        // i.e., each of them becomes a root node
        node->left = dfs(result, toDelete, node->left, deleted);
        node->right = dfs(result, toDelete, node->right, deleted);
        return deleted ? nullptr : node;
    }
};
