#include <vector>

/**
 * Definition for a Node.
 *
 */
class Node
{
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val)
    {
        val = _val;
        left = nullptr;
        right = nullptr;
    }

    Node(int _val, Node* _left, Node* _right)
    {
        val = _val;
        left = _left;
        right = _right;
    }
};

/**
 * Convert a Binary Search Tree to a sorted Circular Doubly-Linked List in place.
 *
 * You can think of the left and right pointers as synonymous to the predecessor and successor
 * pointers in a doubly-linked list. For a circular doubly linked list, the predecessor of the first
 * element is the last element, and the successor of the last element is the first element.
 *
 * We want to do the transformation in place. After the transformation, the left pointer of the tree
 * node should point to its predecessor, and the right pointer should point to its successor. You
 * should return the pointer to the smallest element of the linked list.
 *
 * The number of nodes in the tree is in the range [0, 2000].
 * -1000 <= Node.val <= 1000
 * All the values of the tree are unique.
 */

class Solution
{
public:
    Node* treeToDoublyList(Node* root)
    {
        if (!root)
            return nullptr;

        auto* leftHead = treeToDoublyList(root->left);
        auto* rightHead = treeToDoublyList(root->right);
        Node* leftTail = nullptr;
        Node* rightTail = nullptr;
        if (leftHead) {
            leftTail = leftHead->left;
            root->left = leftTail;
            leftTail->right = root;
        } else {
            leftHead = root;
            leftTail = root;
        }
        if (rightHead) {
            rightTail = rightHead->left;
            root->right = rightHead;
            rightHead->left = root;
        } else {
            rightHead = root;
            rightTail = root;
        }
        leftHead->left = rightTail;
        rightTail->right = leftHead;
        return leftHead;
    }

private:
    Node* approach1(Node* root)
    {
        if (!root)
            return nullptr;

        std::vector<Node*> inorder;
        traverse(inorder, root);
        for (int i = 0; i < inorder.size() - 1; ++i) {
            inorder[i]->right = inorder[i + 1];
            inorder[i + 1]->left = inorder[i];
        }
        inorder.back()->right = inorder.front();
        inorder.front()->left = inorder.back();
        return inorder[0];
    }

    void traverse(std::vector<Node*>& inorder, Node* node)
    {
        if (!node)
            return;

        traverse(inorder, node->left);
        inorder.push_back(node);
        traverse(inorder, node->right);
    }
};