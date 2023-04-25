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
 * Given the "root" of a binary tree, return an array of the largest value in each row of the tree
 * (0-indexed);
 */

class Solution
{
public:
    std::vector<int> largestValue(TreeNode* root)
    {
        if (!root)
            return {};

        std::queue<TreeNode*> queue;
        queue.push(root);
        std::vector<int> result;
        while (!queue.empty()) {
            const auto size = queue.size(); // this level
            int maxVal = INT_MIN;           // this level
            for (size_t i = 0; i < size; ++i) {
                auto* node = queue.front();
                queue.pop();
                maxVal = std::max(maxVal, node->val);
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            result.push_back(maxVal);
        }
        return result;
    }
};