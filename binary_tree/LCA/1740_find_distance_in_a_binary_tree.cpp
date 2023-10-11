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
 * Given the root of a binary tree and two integers p and q, return the distance between the nodes
 * of value p and value q in the tree.
 *
 * The distance between two nodes is the number of edges on the path from one to the other.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! 0 <= Node.val <= 10^9
 * ! All Node.val are unique.
 * ! p and q are values in the tree.
 */

class Solution
{
public:
    int findDistance(TreeNode* root, int p, int q)
    {
        // distance of p and q = depth of p + depth of q - 2 * depth of LCA
        if (!root)
            return -1;

        // our dfs function can't handle the case of p == q, so check it first
        // it is guaranteed that both p and q exist in "root"
        if (p == q)
            return 0;

        dfs(root, p, q, 0);
        return depthLCA == -1 ? -1 : depthP + depthQ - 2 * depthLCA;
    }

private:
    int depthLCA = -1;
    int depthP = -1;
    int depthQ = -1;

    // num of target values exist in "root"
    // #NOTE# make sure p != q
    int dfs(TreeNode* root, int p, int q, int depth)
    {
        if (!root)
            return 0;

        depthP = root->val == p ? depth : depthP;
        depthQ = root->val == q ? depth : depthQ;
        int count = root->val == p || root->val == q ? 1 : 0;
        count += dfs(root->left, p, q, depth + 1);
        count += dfs(root->right, p, q, depth + 1);
        if (count == 2 && depthLCA == -1) {
            depthLCA = depth;
        }
        return count;
    }
};