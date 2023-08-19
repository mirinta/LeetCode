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
    std::vector<int> rightSideView(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> result;
        traverse(result, 0, root);
        return result;
    }

private:
    void traverse(std::vector<int>& result, int level, TreeNode* node)
    {
        if (!node)
            return;

        if (level == result.size()) {
            result.push_back(node->val);
        }
        traverse(result, level + 1, node->right);
        traverse(result, level + 1, node->left);
    }

    // BFS
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
