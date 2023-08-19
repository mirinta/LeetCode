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
 * You are given an integer array "nums" with no duplicates. A maximum binary tree can be built
 * recursively from "nums" using the following algorithm:
 *
 * Great a root node whose value is the maximum in "nums".
 *
 * Recursively build the left subtree on the sub-array prefix to the left of the maximum value.
 *
 * Recursively build the right subtree on the sub-array suffix to the fight of the maximum value.
 *
 * Return the maximum binary tree built from "nums".
 */

class Solution
{
public:
    TreeNode* constructMaximumBinaryTree(const std::vector<int>& nums)
    {
        if (nums.empty())
            return nullptr;

        return construct(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* construct(const std::vector<int>& nums, int low, int high)
    {
        if (low > high)
            return nullptr;

        int max = INT_MIN;
        int idx = low;
        for (int i = low; i <= high; ++i) {
            if (nums[i] > max) {
                idx = i;
                max = nums[i];
            }
        }
        auto* node = new TreeNode(max);
        node->left = construct(nums, low, idx - 1);
        node->right = construct(nums, idx + 1, high);
        return node;
    }
};