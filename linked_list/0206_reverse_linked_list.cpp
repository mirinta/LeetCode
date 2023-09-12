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
 * Given the "head" of a singly linked list, reverse the list, and return the reversed list.
 *
 * ! The number of nodes in the list is the range [0, 5000].
 * ! -5000 <= Node.val <= 5000
 */

class Solution
{
public:
    ListNode* reverseList(ListNode* head) { return approach3(head); }

private:
    // Iterative, time O(N), space O(1)
    ListNode* approach3(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        ListNode* prev = nullptr;
        auto* node = head;
        while (node) {
            auto* next = node->next;
            node->next = prev;
            prev = node;
            node = next;
        }
        return prev;
    }

    // Recursive, time O(N), space O(N)
    ListNode* approach2(ListNode* head)
    {
        // HEAD->X1->X2->...->TAIL
        // =>
        // HEAD->[X1<-X2<-...<-TAIL]
        if (!head || !head->next)
            return head;

        auto* newHead = approach2(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }

    // Stack, time O(N), space O(N)
    ListNode* approach1(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        std::stack<ListNode*> stack;
        while (head) {
            auto* next = head->next;
            head->next = nullptr;
            stack.push(head);
            head = next;
        }
        ListNode vHead(-1);
        auto* node = &vHead;
        while (!stack.empty()) {
            node->next = stack.top();
            stack.pop();
            node = node->next;
        }
        return vHead.next;
    }
};