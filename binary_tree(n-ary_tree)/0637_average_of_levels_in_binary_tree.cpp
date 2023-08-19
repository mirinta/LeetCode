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
 * Given the "root" of a binary tree, return the average value of the nodes on each level in the
 * from of an array. Answers within 10^-5 of the actual answer will be accepted.
 */

class Solution
{
public:
    std::vector<double> averageOfLevels(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<double> result;
        std::queue<TreeNode*> queue;
        queue.push(root);
        double levelSum = 0;
        while (!queue.empty()) {
            const auto size = queue.size();
            levelSum = 0;
            for (size_t i = 0; i < size; ++i) {
                auto* node = queue.front();
                queue.pop();
                levelSum += node->val;
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            result.push_back(levelSum / size);
        }
        return result;
    }
};