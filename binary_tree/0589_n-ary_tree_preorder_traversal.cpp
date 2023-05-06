#include <vector>

/**
 * Definition for a Node.
 */
class Node
{
public:
    int val;
    std::vector<Node*> children;

    Node() {}

    Node(int _val) { val = _val; }

    Node(int _val, std::vector<Node*> _children)
    {
        val = _val;
        children = _children;
    }
};

/**
 * Given the "root" of an n-ary tree, return the preorder traversal of its nodes' values.
 *
 * Nary-Tree input serialization is represented in their level order traversal each group of
 * children is separated by the null value.
 */

class Solution
{
public:
    std::vector<int> preorder(Node* root)
    {
        if (!root)
            return {};

        std::vector<int> result;
        traverse(root, result);
        return result;
    }

private:
    void traverse(Node* node, std::vector<int>& result)
    {
        if (!node)
            return;

        result.push_back(node->val);
        for (auto* child : node->children) {
            traverse(child, result);
        }
    }
};