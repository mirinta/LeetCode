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
 * Populate each next pointer to point to its next right node. If there is no next right node, the
 * next pointer should be set to NULL.
 *
 * Initially, all next pointers are set to NULL.
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
            auto size = queue.size();
            for (size_t i = 0; i < size; ++i) {
                auto* node = queue.front();
                queue.pop();
                node->next = i == size - 1 ? nullptr : queue.front();
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