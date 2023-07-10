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
 * Given an integer array "nums" where the elements are sorted in ascending order, convert it to a
 * height-balanced binary search tree.
 *
 * A height-balanced binary tree is a binary tree in which the depth of the two subtrees of every
 * node never differs by more than one.
 */

class Solution
{
public:
    TreeNode* sortedArrayToBST(const std::vector<int>& nums)
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

        int mid = low + (high - low) / 2;
        auto* node = new TreeNode(nums[mid]);
        node->left = construct(nums, low, mid - 1);
        node->right = construct(nums, mid + 1, high);
        return node;
    }
};