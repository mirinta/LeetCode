#include <queue>
#include <string>

/**
 * Definition of a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * Serialization is the process of converting a data structure or object into a sequence of bits so
 * that it can be stored in a file or memory buffer, or transmitted across a network connection link
 * to be reconstructed later in the same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how
 * your serialization/deserialization algorithm should work. You just need to ensure that a binary
 * tree can be serialized to a string and this string can be deserialized to the original tree
 * structure.
 */

/**
 *    Serialize to                          |   Can deserialize to unique binary tree
 * ------------------------------------------------------------------------------------
 * 1. one traversal order w/o nullptr info  |   NO
 * 2. preorder + inorder w/o nullptr info   |   YES
 * 3. postorder + inorder w/o nullptr info  |   YES
 * 4. preorder + postorder w/o nullptr info |   YES (if all the values are unique)
 * 5. preorder w/ nullptr info              |   YES
 * 6. postorder w/ nullptr info             |   YES
 * 7. inorder w/ nullptr info               |   YES (if all the values are unique)
 */

class Codec
{
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root)
    {
        if (!root)
            return {};

        std::string s{};
        preorderSerialize(root, s);
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(const std::string& data)
    {
        if (data.empty())
            return nullptr;

        std::queue<std::string> preorder;
        for (size_t i = 0, j = 0; j < data.size(); ++j) {
            if (data[j] == k_separator) {
                preorder.push(data.substr(i, j - i));
                i = j + 1;
            }
        }
        return preorderDeserialize(preorder);
    }

private:
    static constexpr char k_separator = ',';
    const std::string k_nullptr{"null"};

    void preorderSerialize(TreeNode* node, std::string& s)
    {
        if (!node) {
            s.append(k_nullptr);
            s.push_back(k_separator); // an extra "," at the end
            return;
        }
        s.append(std::to_string(node->val));
        s.push_back(k_separator);
        preorderSerialize(node->left, s);
        preorderSerialize(node->right, s);
    }

    TreeNode* preorderDeserialize(std::queue<std::string>& preorder)
    {
        if (preorder.empty())
            return nullptr;

        const auto str = preorder.front();
        preorder.pop();
        if (str == k_nullptr)
            return nullptr;

        auto* node = new TreeNode(std::stoi(str));
        node->left = preorderDeserialize(preorder);
        node->right = preorderDeserialize(preorder);
        return node;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));