#include <queue>
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
    // BFS, time O(N), space O(N)
    bool approach2(TreeNode* root)
    {
        if (!root)
            return true;

        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            const int n = queue.size();
            std::vector<int> nums(n);
            for (int i = 0; i < n; ++i) {
                auto* node = queue.front();
                queue.pop();
                nums[i] = node ? node->val : INT_MIN; // Node.val is in the range [-100,100]
                if (node) {
                    queue.push(node->left);
                    queue.push(node->right);
                }
            }
            for (int i = 0, j = n - 1; i <= j; ++i, --j) {
                if (nums[i] != nums[j])
                    return false;
            }
        }
        return true;
    }

    // DFS, time O(N), space O(N)
    bool approach1(TreeNode* root)
    {
        if (!root)
            return true;

        return dfs(root->left, root->right);
    }

    bool dfs(TreeNode* p, TreeNode* q)
    {
        if (!p && !q)
            return true;

        if (!p || !q)
            return false;

        if (p->val != q->val)
            return false;

        // symmetric: p->left is the same as q->right, and p->right is the same as q->left
        return dfs(p->left, q->right) && dfs(p->right, q->left);
    }
};