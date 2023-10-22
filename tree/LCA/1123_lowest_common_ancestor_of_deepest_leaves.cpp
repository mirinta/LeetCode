#include <unordered_map>

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
 * Given the root of a binary tree, return the lowest common ancestor of its deepest leaves.
 *
 * Recall that:
 *
 * - The node of a binary tree is a leaf if and only if it has no children.
 *
 * - The depth of the root of the tree is 0. if the depth of a node is d, the depth of each of its
 * children is d + 1.
 *
 * - The lowest common ancestor of a set S of nodes, is the node A with the largest depth such that
 * every node in S is in the subtree with root A.
 *
 * ! This question is the same as 865.
 *
 * ! The number of nodes in the tree will be in the range [1, 1000].
 * ! 0 <= Node.val <= 1000
 * ! The values of the nodes in the tree are unique.
 */

class Solution
{
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root)
    {
        if (!root)
            return nullptr;

        preorder(root, 0);
        for (const auto& [val, depth] : map) {
            if (depth == maxDepth) {
                numOfDeepestLeaves++;
            }
        }
        postorder(root);
        return result;
    }

private:
    TreeNode* result = nullptr;
    int maxDepth = 0;
    int numOfDeepestLeaves = 0;
    std::unordered_map<int, int> map; // val to depth, use vals as keys because Node.val are unique

    void preorder(TreeNode* root, int depth)
    {
        if (!root)
            return;

        map[root->val] = depth;
        maxDepth = std::max(maxDepth, depth);
        preorder(root->left, depth + 1);
        preorder(root->right, depth + 1);
    }

    int postorder(TreeNode* root)
    {
        if (!root)
            return 0;

        int count = map[root->val] == maxDepth ? 1 : 0;
        count += postorder(root->left);
        count += postorder(root->right);
        if (count == numOfDeepestLeaves && !result) {
            result = root;
        }
        return count;
    }
};