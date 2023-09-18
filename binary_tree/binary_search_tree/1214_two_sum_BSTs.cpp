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
 * Given the roots of two binary search trees, root1 and root2, return true if and only if there is
 * a node in the first tree and a node in the second tree whose values sum up to a given integer
 * target.
 *
 * ! The number of nodes in each tree is in the range [1, 5000].
 * ! -10^9 <= Node.val, target <= 10^9
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target)
    {
        return approach2(root1, root2, target);
    }

private:
    bool approach2(TreeNode* root1, TreeNode* root2, int target)
    {
        if (!root1)
            return false;

        if (binarySearch(root2, target - root1->val))
            return true;

        return approach2(root1->left, root2, target) || approach2(root1->right, root2, target);
    }

    bool binarySearch(TreeNode* root, int target)
    {
        if (!root)
            return false;

        if (root->val < target)
            return binarySearch(root->right, target);

        if (root->val > target)
            return binarySearch(root->left, target);

        return true;
    }

    bool approach1(TreeNode* root1, TreeNode* root2, int target)
    {
        std::vector<int> values1;
        std::vector<int> values2;
        // in-order traversal of BST gets an ascending order array
        traverse(values1, root1);
        traverse(values2, root2);
        int i = 0;
        int j = values2.size() - 1;
        while (i < values1.size() && j >= 0) {
            const int sum = values1[i] + values2[j];
            if (sum > target) {
                j--;
            } else if (sum < target) {
                i++;
            } else {
                return true;
            }
        }
        return false;
    }

    void traverse(std::vector<int>& values, TreeNode* root)
    {
        if (!root)
            return;

        traverse(values, root->left);
        values.push_back(root->val);
        traverse(values, root->right);
    }
};
