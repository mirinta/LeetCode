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
 * Given the root of a binary tree, the depth of each node is the shortest distance to the root.
 *
 * Return the smallest subtree such that it contains all the deepest nodes in the original tree.
 *
 * A node is called the deepest if it has the largest depth possible among any node in the entire
 * tree.
 *
 * The subtree of a node is a tree consisting of that node, plus the set of all descendants of that
 * node.
 *
 * ! This question is the same as 1123.
 *
 * ! The number of nodes in the tree will be in the range [1, 500].
 * ! T0 <= Node.val <= 500
 * ! The values of the nodes in the tree are unique.
 */

class Solution
{
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root)
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