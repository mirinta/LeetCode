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

class Solution
{
public:
    std::vector<int> rightSideView(TreeNode* root)
    {
        if (!root)
            return {};

        // version 2: recursion
        std::vector<int> result;
        traverse(result, 0, root);
        return result;

        // version 1: BFS, level order traversal
        // std::vector<int> result;
        // std::queue<TreeNode*> queue;
        // queue.push(root);
        // while (!queue.empty()) {
        //     const auto size = queue.size();
        //     for (size_t i = 0; i < size; ++i) {
        //         auto* node = queue.front();
        //         queue.pop();
        //         if (i == size - 1) {
        //             result.push_back(node->val);
        //         }
        //         if (node->left) {
        //             queue.push(node->left);
        //         }
        //         if (node->right) {
        //             queue.push(node->right);
        //         }
        //     }
        // }
        // return result;
    }

private:
    void traverse(std::vector<int>& result, int level, TreeNode* node)
    {
        if (!node)
            return;

        // push_back only once at the same level
        if (level == result.size()) {
            result.push_back(node->val);
        }
        traverse(result, level + 1, node->right); // right side first
        traverse(result, level + 1, node->left);
    }
};