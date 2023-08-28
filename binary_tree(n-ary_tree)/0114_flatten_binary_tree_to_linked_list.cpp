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
 * Given the "root" of a binary tree, flatten the tree into a "linked list":
 *
 * - The "linked list" should use the same "TreeNode" class there the "right" child pointer points
 * to the next node in the list and the "left" child pointer is always nullptr.
 *
 * - The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 *
 * ! The number of nodes in the tree is in the range [0, 2000].
 * ! -100 <= Node.val <= 100
 */

class Solution
{
public:
    void flatten(TreeNode* root)
    {
        if (!root)
            return;

        // solve sub-problems
        flatten(root->left);
        flatten(root->right);
        // backup flattened head nodes
        auto* left = root->left;   // e.g., 2->3->4
        auto* right = root->right; // e.g., 5->6
        // construct the linked list
        root->left = nullptr;
        root->right = left; // e.g., 1->2->3->4
        // find the last node
        auto* last = root;
        while (last->right) {
            last = last->right;
        }
        last->right = right; // e.g., 1->2->3->4->5->6
    }
};