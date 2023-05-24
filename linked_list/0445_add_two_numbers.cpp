#include <stack>

/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/**
 * You are given two non-empty linked lists representing two non-negative integers. The most
 * significant digit comes first and each of their nods contains a single digit. Add the two numbers
 * and return the sum as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 * ! The number of nodes in each linked list is in the range [1, 100].
 * ! 0 <= Node.val <= 9
 * ! It is guaranteed that the list represents a number that does not have leading zeros.
 */

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        if (!l1 || !l2)
            return nullptr;

        auto stack1 = traverse(l1);
        auto stack2 = traverse(l2);
        ListNode vHead(-1);
        int carry = 0;
        while (!stack1.empty() || !stack2.empty()) {
            const auto v1 = stack1.empty() ? 0 : stack1.top();
            const auto v2 = stack2.empty() ? 0 : stack2.top();
            const auto sum = v1 + v2 + carry;
            carry = sum / 10;
            auto* node = new ListNode(sum % 10);
            node->next = vHead.next;
            vHead.next = node;
            if (!stack1.empty()) {
                stack1.pop();
            }
            if (!stack2.empty()) {
                stack2.pop();
            }
        }
        if (carry > 0) {
            auto* node = new ListNode(carry);
            node->next = vHead.next;
            vHead.next = node;
        }
        return vHead.next;
    }

private:
    std::stack<int> traverse(ListNode* head)
    {
        if (!head)
            return {};

        std::stack<int> stack;
        while (head) {
            stack.push(head->val);
            head = head->next;
        }
        return stack;
    }
};