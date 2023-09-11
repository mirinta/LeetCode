#include <queue>
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
 * Given the "root" of a binary tree, check whether it is a mirror of itself (i.e., symmetric around
 * its center).
 *
 * ! The number of nodes in the tree is in the range [1, 1000].
 * ! -100 <= Node.val <= 100
 */

class Solution
{
public:
    bool isSymmetric(TreeNode* root) { return approach2(root); }

private:
    // DFS
    bool approach2(TreeNode* root)
    {
        if (!root)
            return false;

        return dfs(root->left, root->right);
    }

    bool dfs(TreeNode* root1, TreeNode* root2)
    {
        // similar to checking whether two binary trees are exactly the same
        if (!root1 && !root2)
            return true;

        if (!root1 || !root2)
            return false;

        if (root1->val != root2->val)
            return false;

        return dfs(root1->left, root2->right) && dfs(root1->right, root2->left);
    }

    // BFS
    bool approach1(TreeNode* root)
    {
        if (!root)
            return false;

        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            const int size = queue.size();
            std::vector<int> values(size);
            for (int k = 0; k < size; ++k) {
                auto* node = queue.front();
                queue.pop();
                values[k] = node ? node->val : INT_MIN; // Node.val is in the range [-100,100]
                if (node) {
                    queue.push(node->left);
                    queue.push(node->right);
                }
            }
            for (int i = 0, j = size - 1; i <= j; ++i, --j) {
                if (values[i] != values[j])
                    return false;
            }
        }
        return true;
    }
};