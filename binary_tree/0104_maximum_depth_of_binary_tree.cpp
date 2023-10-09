#include <queue>

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
    int maxDepth(TreeNode* root) { return approach2(root); }

private:
    // BFS, time O(N), space O(N)
    int approach2(TreeNode* root)
    {
        if (!root)
            return 0;

        int result = 0;
        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            for (int size = queue.size(); size > 0; --size) {
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

    // DFS, time O(N), worst space O(N), best space O(logN)
    int approach1(TreeNode* root)
    {
        if (!root)
            return 0;

        const int leftDepth = approach1(root->left);
        const int rightDepth = approach1(root->right);
        return 1 + std::max(leftDepth, rightDepth);
    }
};

