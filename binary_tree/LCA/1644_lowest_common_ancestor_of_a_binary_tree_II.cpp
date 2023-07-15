/**
 Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Given the root of a binary tree, return the lowest common ancestor (LCA) of two given nodes, p
 * and q. If either node p or q does not exist in the tree, return null. All values of the nodes in
 * the tree are unique.
 *
 * According to the definition of LCA on Wikipedia: "The lowest common ancestor of two nodes p and q
 * in a binary tree T is the lowest node that has both p and q as descendants (where we allow a node
 * to be a descendant of itself)". A descendant of a node x is a node y that is on the path from
 * node x to some leaf node.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -10^9 <= Node.val <= 10^9
 * ! All Node.val are unique.
 * ! p != q
 */

class Solution
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        return approach2(root, p, q);
    }

private:
    TreeNode* result = nullptr;

    TreeNode* approach2(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (!root || !p || !q)
            return nullptr;

        dfs(root, p->val, q->val);
        return result;
    }

    // return 0, root doesn't contain val1 and val2
    // return 1, root contains val1 or val2
    // return 2, root contains both val1 and val2
    int dfs(TreeNode* root, int val1, int val2)
    {
        if (!root)
            return 0;

        const int left = dfs(root->left, val1, val2);
        const int right = dfs(root->right, val1, val2);
        const int self = root->val == val1 || root->val == val2;
        const int count = left + right + self;
        if (count == 2 && !result) {
            result = root;
        }
        return count;
    }
    //-----------------------------------------------------
    bool isPFound = false;
    bool isQFound = false;

    TreeNode* approach1(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (!root || !p || !q)
            return nullptr;

        auto* result = find(root, p->val, q->val);
        if (isPFound && isQFound)
            return result;

        return nullptr;
    }

    TreeNode* find(TreeNode* root, int valueOfP, int valueOfQ)
    {
        if (!root)
            return nullptr;

        auto* left = find(root->left, valueOfP, valueOfQ);
        auto* right = find(root->right, valueOfP, valueOfQ);
        if (root->val == valueOfP) {
            isPFound = true;
            return root;
        }
        if (root->val == valueOfQ) {
            isQFound = true;
            return root;
        }
        if (left && right)
            return root;

        return left ? left : right;
    }
};