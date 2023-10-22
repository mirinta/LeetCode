#include <queue>

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
 * Given the "root" of a binary tree, return its maximum depth.
 *
 * A binary tree's maximum depth is the number of nodes along the longest path from the root node
 * down to the farthest leaf node.
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! -100 <= Node.val <= 100
 */

class Solution
{
public:
    int maxDepth(TreeNode* root)
    {
        // return bfs(root);
        return dfs(root);
    }

private:
    // approach1, post-order traversal
    int dfs(TreeNode* root)
    {
        if (!root)
            return 0;

        return 1 + std::max(dfs(root->left), dfs(root->right));
    }

    // approach2, level-order traversal
    int bfs(TreeNode* root)
    {
        if (!root)
            return 0;

        int result = 0;
        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            for (int i = queue.size(); i > 0; --i) {
                auto* node = queue.front();
                queue.pop();
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            result++;
        }
        return result;
    }
};
