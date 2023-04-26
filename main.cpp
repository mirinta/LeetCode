#include <iostream>
#include <memory>
#include <vector>
struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

size_t sum0toN(size_t n)
{
    std::cout << n << ", before base" << '\n';
    if (n == 0) {
        std::cout << n << ", reach base" << '\n';
        return 0;
    }
    std::cout << n << ", before recursion" << '\n';
    const auto result = n + sum0toN(n - 1);
    std::cout << n << ", after recursion" << '\n';
    return result;
}

void testRecursion()
{
    std::cout << "---begin---" << '\n';
    sum0toN(5);
    std::cout << "---end---" << '\n';
}

void printListForward(ListNode* head)
{
    if (!head) {
        std::cout << '\n';
        return;
    }

    std::cout << head->val;
    if (head->next) {
        std::cout << "->";
    }
    printListForward(head->next);
}

void printListBackward(ListNode* head)
{
    if (!head)
        return;

    printListBackward(head->next);
    std::cout << head->val << "->";
}

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val, TreeNode* left, TreeNode* right) : val(val), left(left), right(right) {}
    TreeNode(int val) : TreeNode(val, nullptr, nullptr) {}
    TreeNode() : TreeNode(0) {}
};

void traverse(TreeNode* node, std::vector<int>& preorder, std::vector<int>& inorder,
              std::vector<int>& postorder)
{
    if (!node)
        return;

    preorder.push_back(node->val);
    traverse(node->left, preorder, inorder, postorder);
    inorder.push_back(node->val);
    traverse(node->right, preorder, inorder, postorder);
    postorder.push_back(node->val);
}

int main()
{
    TreeNode n1(1);
    TreeNode n2(2);
    TreeNode n3(3);
    TreeNode n4(4);
    TreeNode n5(5);
    TreeNode n6(6);
    TreeNode n7(7);
    TreeNode n8(8);
    TreeNode n9(9);

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n5;
    n2.right = &n4;
    n3.left = &n8;
    n3.right = &n9;
    n4.left = &n6;
    n4.right = &n7;

    std::vector<int> preorder;
    std::vector<int> inorder;
    std::vector<int> postorder;
    traverse(&n1, preorder, inorder, postorder);
    std::cout << '\n';
}
