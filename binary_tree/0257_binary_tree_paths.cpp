#include <string>
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
    std::vector<std::string> binaryTreePaths(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<std::string> result;
        std::vector<int> values;
        traverse(root, values, result);
        return result;
    }

private:
    void traverse(TreeNode* node, std::vector<int>& values, std::vector<std::string>& result)
    {
        if (!node)
            return;

        if (!node->left && !node->right) {
            std::string concat;
            for (const auto& value : values) {
                concat.append(std::to_string(value));
                concat.append("->");
            }
            concat.append(std::to_string(node->val));
            result.push_back(std::move(concat));
            return;
        }
        values.push_back(node->val);
        traverse(node->left, values, result);
        traverse(node->right, values, result);
        values.pop_back(); // process finished, pop the current value
    }
};
