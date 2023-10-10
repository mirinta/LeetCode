#include <string>
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
 * Given the root of a binary tree, return all root-to-leaf paths in any order.
 *
 * A leaf is a node with no children.
 *
 * ! The number of nodes in the tree is in the range [1, 100].
 * ! -100 <= Node.val <= 100
 */

class Solution
{
public:
    std::vector<std::string> binaryTreePaths(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<std::string> result;
        std::vector<std::string> path;
        dfs(result, path, root);
        return result;
    }

private:
    void dfs(std::vector<std::string>& result, std::vector<std::string>& path, TreeNode* root)
    {
        if (!root)
            return;

        if (!root->left && !root->right) {
            std::string concatenation;
            for (const auto& s : path) {
                concatenation.append(s);
                concatenation.append("->");
            }
            concatenation.append(std::to_string(root->val));
            result.push_back(concatenation);
        }
        path.push_back(std::to_string(root->val));
        dfs(result, path, root->left);
        dfs(result, path, root->right);
        path.pop_back();
    }
};
