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
 * Given an integer n, return a list of all possible full binary trees with n nodes. Each node of
 * each tree in the answer must have Node.val == 0.
 *
 * Each element of the answer is the root node of one possible tree. You may return the final list
 * of trees in any order.
 *
 * A full binary tree is a binary tree where each node has exactly 0 or 2 children.
 *
 * ! 1 <= n <= 20
 */

class Solution
{
public:
    std::vector<TreeNode*> allPossibleFBT(int n)
    {
        if (n % 2 == 0)
            return {};

        memo = std::vector<std::vector<TreeNode*>>(n + 1);
        return dp(n);
    }

private:
    std::vector<std::vector<TreeNode*>> memo;

    std::vector<TreeNode*> dp(int n)
    {
        if (n < 0)
            return {};

        if (!memo[n].empty())
            return memo[n];

        if (n == 1)
            return {new TreeNode(0)};

        std::vector<TreeNode*> result;
        for (int leftNodes = 1; leftNodes <= n - 1; leftNodes += 2) {
            const int rightNodes = n - leftNodes - 1;
            const auto leftFBTs = dp(leftNodes);
            const auto rightFBTs = dp(rightNodes);
            for (auto* const left : leftFBTs) {
                for (auto* const right : rightFBTs) {
                    auto* root = new TreeNode(0);
                    root->left = left;
                    root->right = right;
                    result.push_back(root);
                }
            }
        }
        memo[n] = std::move(result);
        return memo[n];
    };
};
