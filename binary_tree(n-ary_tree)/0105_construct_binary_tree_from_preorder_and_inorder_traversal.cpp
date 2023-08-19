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
 * Given two integer arrays "preorder" and "inorder" where "preorder" is the preorder traversal of a
 * binary tree and "inorder" is the inorder traversal of the same tree, construct and return the
 * binary tree.
 *
 * ! "preorder" and "inorder" consist of unique values.
 */

class Solution
{
public:
    TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder)
    {
        if (preorder.size() != inorder.size() || preorder.empty())
            return nullptr;

        for (size_t i = 0; i < inorder.size(); ++i) {
            valToIdx[inorder[i]] = i;
        }
        return build(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

private:
    std::unordered_map<int, int> valToIdx; // value = index of the "inorder" array
    TreeNode* build(const std::vector<int>& preorder, int preStart, int preEnd,
                    const std::vector<int>& inorder, int inStart, int inEnd)
    {
        // Example:
        //    index = [0, 1,  2,  3, 4]
        // preorder = [3, 9, 20, 15, 7]
        //  inorder = [9, 3, 15, 20, 7]
        if (preStart > preEnd)
            return nullptr;

        const int rootVal = preorder[preStart]; // suppose the value is 3
        const int index = valToIdx[rootVal];    // the index of current root node in "inorder"
        const int nodes = index - inStart;      // #nodes of the left subtree
        // construct the current node
        auto* root = new TreeNode(rootVal);
        // to construct the left side, we need preorder = [9], inorder = [9]
        root->left = build(preorder, preStart + 1, preStart + nodes, inorder, inStart, index - 1);
        // to construct the right side, we need preorder = [20, 15, 7], inorder = [15, 20, 7]
        root->right = build(preorder, preStart + nodes + 1, preEnd, inorder, index + 1, inEnd);
        return root;
    }
};