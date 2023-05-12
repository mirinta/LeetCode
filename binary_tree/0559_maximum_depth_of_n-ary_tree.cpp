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
 * Given a n-ary tree, find its maximum depth.
 *
 * The maximum depth is the number of nodes along the longest path from the root node down to the
 * farthest leaf node.
 *
 * Nary-Tree input serialization is represented in their level order traversal, each group of
 * children is separated by the null value.
 */

class Solution
{
public:
    int maxDepth(Node* root)
    {
        if (!root)
            return 0;

        // approach 2: recursion
        int depth = 0;
        for (auto* node : root->children) {
            depth = std::max(depth, maxDepth(node));
        }
        return depth + 1;

        // approach 1: level order traversal
        // std::queue<Node*> queue;
        // queue.push(root);
        // int maxDepth = 0;
        // while (!queue.empty()) {
        //     const auto size = queue.size();
        //     for (size_t i = 0; i < size; ++i) {
        //         auto* node = queue.front();
        //         queue.pop();
        //         for (auto* child : node->children) {
        //             if (child) {
        //                 queue.push(child);
        //             }
        //         }
        //     }
        //     maxDepth++;
        // }
        // return maxDepth;
    }
};