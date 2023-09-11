#include <queue>
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
 * Given the root of a binary tree, imagine yourself standing on the right side of it, return the
 * values of the nodes you can see ordered from top to bottom.
 *
 * ! The number of nodes in the tree is in the range [0, 100].
 * ! -100 <= Node.val <= 100
 */

class Solution
{
public:
    std::vector<int> rightSideView(TreeNode* root) { return approach2(root); }

private:
    // Pre-order traversal (right subtree first)
    std::vector<int> approach2(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> result;
        dfs(result, 0, root);
        return result;
    }

    void dfs(std::vector<int>& result, int level, TreeNode* node)
    {
        if (!node)
            return;

        /**   1 <= level 0
         *    / \
         *   2   3 <= level 1
         *    \   \
         *     5   4 <= level 2
         */
        if (level == result.size()) {
            result.push_back(node->val);
        }
        dfs(result, level + 1, node->right);
        dfs(result, level + 1, node->left);
    }

    // Level order traversal
    std::vector<int> approach1(TreeNode* root)
    {
        if (!root)
            return {};

        std::queue<TreeNode*> queue;
        queue.push(root);
        std::vector<int> result;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int i = 0; i < size; ++i) {
                auto* node = queue.front();
                queue.pop();
                if (i == size - 1) {
                    result.push_back(node->val);
                }
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
        }
        return result;
    }
};