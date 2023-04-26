#include <unordered_map>
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
 * Given two integer arrays, "preorder" and "postorder" where "preorder" is the preorder traversal
 * of a binary tree of distinct values and "postorder" is the postorder traversal of the same tree,
 * reconstruct and return the binary tree.
 *
 * If there exist multiple answers, you can return any of them.
 *
 * ! All the values of "postorder" are unique.
 */

class Solution
{
public:
    TreeNode* constructFromPrePost(const std::vector<int>& preorder,
                                   const std::vector<int>& postorder)
    {
        if (preorder.size() != postorder.size() || preorder.empty())
            return nullptr;

        for (size_t i = 0; i < postorder.size(); ++i) {
            valToIndex[postorder[i]] = i;
        }
        return construct(preorder, 0, preorder.size() - 1, postorder, 0, postorder.size() - 1);
    }

private:
    std::unordered_map<int, int> valToIndex; // index of node in "postorder"
    TreeNode* construct(const std::vector<int>& preorder, int preStart, int preEnd,
                        const std::vector<int>& postorder, int postStart, int postEnd)
    {
        if (preStart > preEnd)
            return nullptr;

        if (preStart == preEnd)
            return new TreeNode(preorder[preStart]);

        const auto rootVal = preorder[preStart];
        const auto leftNodeVal = preorder[preStart + 1];  // assume preStart+1 is the left node
        const auto leftNodeIdx = valToIndex[leftNodeVal]; // in "postorder"
        const auto leftSize = leftNodeIdx - postStart + 1;
        auto* root = new TreeNode(rootVal);
        root->left = construct(preorder, preStart + 1, preStart + leftSize, postorder, postStart,
                               postStart + leftSize - 1);
        root->right = construct(preorder, preStart + leftSize + 1, preEnd, postorder,
                                postStart + leftSize, postEnd - 1);
        return root;
    }
};