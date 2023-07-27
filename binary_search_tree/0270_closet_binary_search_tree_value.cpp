#include <algorithm>
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
 * Given the root of a binary search tree and a target value, return the value in the BST that is
 * closest to the target. If there are multiple answers, print the smallest.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! 0 <= Node.val <= 10^9
 * ! -10^9 <= target <= 10^9
 */

class Solution
{
public:
    int closestValue(TreeNode* root, double target)
    {
        if (!root)
            return -1;

        int result = root->val;
        while (root) {
            const auto diff1 = std::abs(result - target);
            const auto diff2 = std::abs(root->val - target);
            if (diff1 > diff2 || (diff1 == diff2 && root->val < result)) {
                result = root->val;
            }
            root = target < root->val ? root->left : root->right;
        }
        return result;
    }

private:
    // inorder traverse all nodes, time O(N), space O(N)
    int approach1(TreeNode* root, double target)
    {
        if (!root)
            return -1;

        std::vector<int> inorder;
        traverse(inorder, root);
        if (target > inorder.back())
            return inorder.back();

        if (target < inorder.front())
            return inorder.front();

        auto iter = std::upper_bound(inorder.begin(), inorder.end(), target);
        const int firstLarger = *iter;
        const int lastSmaller = *std::prev(iter);
        return target - lastSmaller <= firstLarger - target ? lastSmaller : firstLarger;
    }

    void traverse(std::vector<int>& inorder, TreeNode* node)
    {
        if (!node)
            return;

        traverse(inorder, node->left);
        inorder.push_back(node->val);
        traverse(inorder, node->right);
    }
};