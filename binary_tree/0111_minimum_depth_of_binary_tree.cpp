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
 * Given a binary tree, find its minimum depth.
 *
 * The minimum depth is the number of nodes along the shortest path from the root node down to the
 * nearest leaf node.
 */

class Solution
{
public:
    int minDepth(TreeNode* root)
    {
        if (!root)
            return 0;

        // BFS: level traverse
        int result = 1;
        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            const auto size = queue.size();
            for (size_t i = 0; i < size; ++i) {
                auto* node = queue.front();
                queue.pop();
                if (!node->left && !node->right)
                    return result;

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