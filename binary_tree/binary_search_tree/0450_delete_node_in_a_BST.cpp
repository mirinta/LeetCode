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
 * Given a root node reference of a BST and a key, delete the node with the given key in the BST.
 * Return the root node reference (possibly) updated of the BST.
 *
 * Basically, the deletion can be divided into two stages:
 *
 * - Search for a node to remove.
 *
 * - If the node is found, delete the node.
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! -10^5 <= Node.val <= 10^5
 * ! Each node has a unique value.
 * ! root is a valid binary search tree.
 * ! -10^5 <= key <= 10^5
 */

class Solution
{
public:
    TreeNode* deleteNode(TreeNode* root, int key)
    {
        if (!root)
            return nullptr;

        if (root->val == key) {
            // case 1: it is a leaf node (this case can be merged into case 2 or case 3)
            if (!root->left && !root->right)
                return nullptr;
            // case 2: it only has right node (left node is nullptr)
            if (!root->left)
                return root->right;
            // case 3: it only has left node (right node is nullptr)
            if (!root->right)
                return root->left;
            // case 4: it has both left and right nodes
            // replace with the min node in right subtree
            auto* minNodeOfRight = root->right;
            while (minNodeOfRight && minNodeOfRight->left) {
                minNodeOfRight = minNodeOfRight->left;
            }
            root->right = deleteNode(root->right, minNodeOfRight->val);
            minNodeOfRight->left = root->left;
            minNodeOfRight->right = root->right;
            return minNodeOfRight;
        }
        if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else {
            root->right = deleteNode(root->right, key);
        }
        return root;
    }
};
