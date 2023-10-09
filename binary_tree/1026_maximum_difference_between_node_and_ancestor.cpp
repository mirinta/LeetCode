#include <utility>

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
 * Given the root of a binary tree, find the maximum value v for which there exist different nodes a
 * and b where v = |a.val - b.val| and a is an ancestor of b.
 *
 * A node a is an ancestor of b if either: any child of a is equal to b or any child of a is an
 * ancestor of b.
 *
 * ! The number of nodes in the tree is in the range [2, 5000].
 * ! 0 <= Node.val <= 10^5
 */

class Solution
{
public:
    int maxAncestorDiff(TreeNode* root)
    {
        if (!root)
            return -1;

        // assume a path is A1->...->An->B, {A1,...,An} are ancestors of B
        // standing at B, we want max(|Ai.val - B.val|)
        // since B.val is fixed, we only need the max_val = max(Ai.val) and min_val = min(Ai.val),
        // then max(|Ai.val - B.val|) = max(|max_val - B.val|, |min_val - B.val|)
        int result = 0;
        dfs(result, root->val, root->val, root);
        return result;
    }

private:
    void dfs(int& result, int min, int max, TreeNode* root)
    {
        if (!root)
            return;

        result = std::max({result, std::abs(root->val - min), std::abs(root->val - max)});
        min = std::min(min, root->val);
        max = std::max(max, root->val);
        dfs(result, min, max, root->left);
        dfs(result, min, max, root->right);
    }
};