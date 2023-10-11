#include <string>

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
 * You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from
 * 1 to n. You are also given an integer startValue representing the value of the start node s, and
 * a different integer destValue representing the value of the destination node t.
 *
 * Find the shortest path starting from node s and ending at node t. Generate step-by-step
 * directions of such path as a string consisting of only the uppercase letters 'L', 'R', and 'U'.
 * Each letter indicates a specific direction:
 *
 * - 'L' means to go from a node to its left child node.
 *
 * - 'R' means to go from a node to its right child node.
 *
 * - 'U' means to go from a node to its parent node.
 *
 * Return the step-by-step directions of the shortest path from node s to node t.
 *
 * ! The number of nodes in the tree is n.
 * ! 2 <= n <= 10^5
 * ! 1 <= Node.val <= n
 * ! All the values in the tree are unique.
 * ! 1 <= startValue, destValue <= n
 * ! startValue != destValue
 */

class Solution
{
public:
    std::string getDirections(TreeNode* root, int startValue, int destValue)
    {
        if (!root)
            return {};

        // it is guaranteed that "startValue" and "destValue" exist in the tree
        // - the LCA of start node and destination node exists
        // - the path from LCA to start node exists
        // - the path from LCA to destination node exists
        dfs(root, startValue, destValue);
        std::string result;
        backtrack(result, lca, startValue);
        std::fill(result.begin(), result.end(), 'U');
        backtrack(result, lca, destValue);
        return result;
    }

private:
    TreeNode* lca = nullptr;

    int dfs(TreeNode* root, int val1, int val2)
    {
        if (!root)
            return 0;

        int count = root->val == val1 || root->val == val2 ? 1 : 0;
        count += dfs(root->left, val1, val2);
        count += dfs(root->right, val1, val2);
        if (count == 2 && !lca) {
            lca = root;
        }
        return count;
    }

    bool backtrack(std::string& path, TreeNode* root, int targetVal)
    {
        if (!root)
            return false;

        if (root->val == targetVal)
            return true;

        path.push_back('L');
        if (backtrack(path, root->left, targetVal))
            return true;

        path.pop_back();
        path.push_back('R');
        if (backtrack(path, root->right, targetVal))
            return true;

        path.pop_back();
        return false;
    }
};