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
 */

class Solution
{
public:
    // version 1: BFS
    // Node* connect(Node* root)
    // {
    //     if (!root)
    //         return nullptr;

    //     std::queue<Node*> queue;
    //     queue.push(root);
    //     while (!queue.empty()) {
    //         const auto size = queue.size();
    //         // connect the nodes on the same level {X0, X1, ..., Xn}
    //         // Xi->next = X(i+1), for the last node, Xn->next = nullptr
    //         for (size_t i = 0; i < size; ++i) {
    //             auto* node = queue.front();
    //             queue.pop();
    //             node->next = i == size - 1 ? nullptr : queue.front();
    //             if (node->left) {
    //                 queue.push(node->left);
    //             }
    //             if (node->right) {
    //                 queue.push(node->right);
    //             }
    //         }
    //     }
    //     return root;
    // }
    // version 2: "trinary" tree
    Node* connect(Node* root)
    {
        if (!root)
            return nullptr;

        traverse(root->left, root->right);
        return root;
    }

private:
    void traverse(Node* node1, Node* node2)
    {
        if (!node1 || !node2)
            return;

        node1->next = node2;
        traverse(node1->left, node1->right); // connect the child nodes of the same parent
        traverse(node2->left, node2->right); // connect the child nodes of the same parent
        traverse(node1->right, node2->left); // connect the child nodes of different parent nodes
    }
};