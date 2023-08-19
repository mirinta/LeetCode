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
 * Given two integer arrays "inorder" and "postorder" where "inorder" is the inorder traversal of a
 * binary tree and "postorder" is the postorder traversal of the same tree, construct and return the
 * binary tree.
 *
 * ! "inorder" and "postorder" consist of unique values.
 */

class Solution
{
public:
    TreeNode* buildTree(const std::vector<int>& inorder, const std::vector<int>& postorder)
    {
        if (inorder.size() != postorder.size() || inorder.empty())
            return nullptr;

        for (size_t i = 0; i < inorder.size(); ++i) {
            valToIndex[inorder[i]] = i;
        }
        return build(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }

private:
    std::unordered_map<int, int> valToIndex; // node value to index in "inorder"
    TreeNode* build(const std::vector<int>& inorder, int inStart, int inEnd,
                    const std::vector<int>& postorder, int postStart, int postEnd)
    {
        if (inStart > inEnd)
            return nullptr;

        // inorder = [9, 3, 15, 20, 7], postorder = [9, 15, 7, 20, 3]
        // suppose we want to build the root node (value = 3)
        int rootVal = postorder[postEnd];
        int index = valToIndex[rootVal]; // index of the root node in "inorder"
        int leftSize = index - inStart;  // #nodes of the left subtree
        // construct the node
        auto* node = new TreeNode(rootVal);
        // to construct the left side, we need inorder = 9, postorder = [9]
        node->left =
            build(inorder, inStart, index - 1, postorder, postStart, postStart + leftSize - 1);
        // to construct the right side, we need inorder = [15, 20, 7], postorder = [15, 7, 20]
        node->right =
            build(inorder, index + 1, inEnd, postorder, postStart + leftSize, postEnd - 1);
        return node;
    }
};