#include <queue>
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
 * Given the root of a binary tree, return the zigzag level order traversal of its nodes' values.
 * (i.e., from left to right, then right to left for the next level and alternate between).
 *
 * ! The number of nodes in the tree is in the range [0, 2000].
 * ! -100 <= Node.val <= 100
 */

class Solution
{
public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<std::vector<int>> result;
        std::queue<TreeNode*> queue;
        queue.push(root);
        bool reverse = false;
        while (!queue.empty()) {
            const int n = queue.size();
            std::vector<int> level(n, 0);
            for (int i = reverse ? n - 1 : 0; reverse ? i >= 0 : i < n; reverse ? --i : ++i) {
                auto* node = queue.front();
                queue.pop();
                level[i] = node->val;
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            result.push_back(std::move(level));
            reverse = !reverse;
        }
        return result;
    }
};