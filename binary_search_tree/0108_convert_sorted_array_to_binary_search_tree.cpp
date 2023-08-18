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
 *
 * ! 1 <= nums.length <= 10^4
 * ! -10^4 <= nums[i] <= 10^4
 * ! nums is sorted in a strictly increasing order.
 */

class Solution
{
public:
    TreeNode* sortedArrayToBST(std::vector<int>& nums)
    {
        if (nums.empty())
            return nullptr;

        return build(0, nums.size() - 1, nums);
    }

private:
    TreeNode* build(int lo, int hi, const std::vector<int>& nums)
    {
        if (lo > hi)
            return nullptr;

        const int mid = lo + (hi - lo) / 2;
        auto* root = new TreeNode(nums[mid]);
        root->left = build(lo, mid - 1, nums);
        root->right = build(mid + 1, hi, nums);
        return root;
    }
};
