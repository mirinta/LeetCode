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
 * Given the "root" of a binary tree, check whether it is a mirror of itself (i.e., symmetric around
 * its center).
 */

class Solution
{
private:
    bool compare(TreeNode* node1, TreeNode* node2)
    {
        if (!node1 || !node2)
            return node1 == node2;

        if (node1->val != node2->val)
            return false;

        return compare(node1->left, node2->right) && compare(node1->right, node2->left);
    }

public:
    // version 2: recursion
    // bool isSymmetric(TreeNode* root)
    // {
    //     if (!root)
    //         return false;

    //     return compare(root->left, root->right);
    // }
    // version 1: level order traversal
    bool isSymmetric(TreeNode* root)
    {
        if (!root)
            return false;

        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            std::vector<TreeNode*> nodes(queue.size(), nullptr);
            for (auto& node : nodes) {
                node = queue.front();
                queue.pop();
                if (node) {
                    queue.push(node->left);
                    queue.push(node->right);
                }
            }
            for (size_t i = 0, j = nodes.size() - 1; i < j; ++i, --j) {
                auto* left = nodes[i];
                auto* right = nodes[j];
                if (left && !right)
                    return false;

                if (!left && right)
                    return false;

                if (left && right && left->val != right->val)
                    return false;
            }
        }
        return true;
    }
};