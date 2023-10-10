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
 * Given two integer arrays "inorder" and "postorder" where "inorder" is the inorder traversal of a
 * binary tree and "postorder" is the postorder traversal of the same tree, construct and return the
 * binary tree.
 *
 * ! 1 <= inorder.length <= 3000
 * ! postorder.length == inorder.length
 * ! -3000 <= inorder[i], postorder[i] <= 3000
 * ! inorder and postorder consist of unique values.
 * ! Each value of postorder also appears in inorder.
 * ! inorder is guaranteed to be the inorder traversal of the tree.
 * ! postorder is guaranteed to be the postorder traversal of the tree.
 */

class Solution
{
public:
    TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder)
    {
        if (inorder.size() != postorder.size() || inorder.empty())
            return nullptr;

        /**
         *        3
         *     /     \
         *    9       8
         *   / \     / \
         *  1   5   6   7
         * / \ / \ / \ / \
         *
         *      index: 0  1  2  3  4  5  6
         *    inorder: 1  9  5  3  6  8  7
         *             |LEFT |  ^  |RIGHT|
         *
         *      index: 0  1  2  3  4  5  6
         *  postorder: 1  5  9  6  7  8  3
         *             |LEFT |  |RIGHT|  ^
         */
        const int n = inorder.size();
        for (int i = 0; i < n; ++i) {
            map[inorder[i]] = i;
        }
        return build(inorder, 0, n - 1, postorder, 0, n - 1);
    }

private:
    std::unordered_map<int, int> map; // node value to index of "inorder"

    TreeNode* build(const std::vector<int>& inorder, int inStart, int inEnd,
                    const std::vector<int>& postorder, int postStart, int postEnd)
    {
        if (inStart > inEnd)
            return nullptr;

        const int rootValue = postorder[postEnd];
        const int index = map[rootValue];
        const int leftSubtreeNodes = index - inStart;
        auto* root = new TreeNode(rootValue);
        root->left = build(inorder, inStart, index - 1, postorder, postStart,
                           postStart + leftSubtreeNodes - 1);
        root->right =
            build(inorder, index + 1, inEnd, postorder, postStart + leftSubtreeNodes, postEnd - 1);
        return root;
    }
};