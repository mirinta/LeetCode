#include <queue>

/**
 * Definition for a Node.
 */
class Node
{
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next)
    {
    }
};

/**
 * You are given a perfect binary tree where all leaves are on the same level, and every parent has
 * two children. The binary tree has the following definitions:
 *
 * struct Node
 * {
 *     int val;
 *     Node* left;
 *     Node* right;
 *     Node* next;
 * };
 *
 * Populate each next pointer to point to its next right node. If there is no next right node, the
 * next pointer should be set to nullptr.
 *
 * Initially, all next pointers are set to nullptr.
 *
 * ! The number of nodes in the tree is in the range [0, 2^12 - 1].
 * ! -1000 <= Node.val <= 1000
 */

class Solution
{
public:
    Node* connect(Node* root)
    {
        if (!root)
            return nullptr;

        std::queue<Node*> queue;
        queue.push(root);
        while (!queue.empty()) {
            for (int i = queue.size(); i > 0; --i) {
                auto* node = queue.front();
                queue.pop();
                node->next = i == 1 ? nullptr : queue.front();
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
        }
        return root;
    }
};