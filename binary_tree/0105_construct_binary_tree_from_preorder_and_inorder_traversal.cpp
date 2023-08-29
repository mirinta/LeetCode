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
 * ! 1 <= preorder.length <= 3000
 * ! inorder.length == preorder.length
 * ! -3000 <= preorder[i], inorder[i] <= 3000
 * ! preorder and inorder consist of unique values.
 * ! Each value of inorder also appears in preorder.
 * ! preorder is guaranteed to be the preorder traversal of the tree.
 * ! inorder is guaranteed to be the inorder traversal of the tree.
 */

class Solution
{
public:
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
    {
        if (preorder.size() != inorder.size() || preorder.empty())
            return nullptr;

        /**
         *        3
         *     /     \
         *    9       8
         *   / \     / \
         *  1   5   6   7
         * / \ / \ / \ / \
         *
         *    index: 0  1  2  3  4  5  6
         * preorder: 3  9  1  5  8  6  7
         *           ^  |LEFT |  |RIGHT|
         *
         *    index: 0  1  2  3  4  5  6
         *  inorder: 1  9  5  3  6  8  7
         *           |LEFT |  ^  |RIGHT|
         */
        const int n = preorder.size();
        map.clear();
        for (int i = 0; i < n; ++i) {
            map[inorder[i]] = i;
        }
        return build(preorder, 0, n - 1, inorder, 0, n - 1);
    }

private:
    std::unordered_map<int, int> map; // node value to index of "inorder"

    TreeNode* build(const std::vector<int>& preorder, int preStart, int preEnd,
                    const std::vector<int>& inorder, int inStart, int inEnd)
    {
        if (preStart > preEnd)
            return nullptr;

        const int rootValue = preorder[preStart];
        const int index = map[rootValue]; // index of the root node in "inorder"
        const int leftSubtreeNodes = index - inStart;
        auto* root = new TreeNode(rootValue);
        root->left =
            build(preorder, preStart + 1, preStart + leftSubtreeNodes, inorder, inStart, index - 1);
        root->right =
            build(preorder, preStart + leftSubtreeNodes + 1, preEnd, inorder, index + 1, inEnd);
        return root;
    }
};