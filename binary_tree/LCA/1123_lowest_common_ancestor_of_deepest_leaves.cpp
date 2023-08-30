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

        // step1: Preprocess
        // - max depth
        // - depth of each node (since all Node.val are unique, we use their values as keys)
        // - num of deepest leaves
        preorderDFS(root, 0);
        // step2: For each node from bottom to top, count the number of deepest leaves it contains.
        // The first node that contains all the deepest leaves is the final answer
        postorderDFS(root);
        return result;
    }

private:
    TreeNode* result = nullptr;
    int maxDepth = 0;
    std::unordered_map<int, int> valueToDepth;
    std::unordered_map<int, int> depthToCount;

    void preorderDFS(TreeNode* node, int currentDepth)
    {
        if (!node)
            return;

        valueToDepth[node->val] = currentDepth;
        depthToCount[currentDepth]++;
        maxDepth = std::max(maxDepth, currentDepth);
        preorderDFS(node->left, currentDepth + 1);
        preorderDFS(node->right, currentDepth + 1);
    }

    int postorderDFS(TreeNode* node)
    {
        if (!node)
            return 0;

        const int self = valueToDepth[node->val] == maxDepth ? 1 : 0;
        const int numOfDeepestLeaves = self + postorderDFS(node->left) + postorderDFS(node->right);
        if (numOfDeepestLeaves == depthToCount[maxDepth] && !result) {
            result = node;
        }
        return numOfDeepestLeaves;
    }
};