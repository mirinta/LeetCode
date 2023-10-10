#include <string>
#include <unordered_map>
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
 * Given the "root" of a binary tree, return all duplicate subtrees.
 *
 * For each kind of duplicate subtrees you only need to return the root node of any one of them.
 *
 * Two trees are duplicate if they have the same structure with the same node values.
 */

class Solution
{
public:
    std::vector<TreeNode*> findDuplicateSubtrees(TreeNode* root)
    {
        if (!root)
            return {};

        traverse(root);
        return result;
    }

private:
    static constexpr char k_separator = ',';
    const std::string k_nullptr = "#";
    std::unordered_map<std::string, int> freq;
    std::vector<TreeNode*> result;

    std::string traverse(TreeNode* node)
    {
        if (!node)
            return k_nullptr;

        auto str = std::to_string(node->val);
        str.push_back(k_separator);
        str.append(traverse(node->left));
        str.push_back(k_separator);
        str.append(traverse(node->right));
        if (freq[str]++ == 1) {
            result.push_back(node);
        }
        return str;
    }
};
