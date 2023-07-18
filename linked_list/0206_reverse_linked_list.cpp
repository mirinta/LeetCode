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
    // iteration
    ListNode* approach3(ListNode* head)
    {
        if (!head)
            return nullptr;

        ListNode* prev = nullptr;
        auto* current = head;
        while (current) {
            auto* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        return prev;
    }

    // recursion
    ListNode* approach2(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        // 0->[1<-2<-...]
        auto* newHead = approach2(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }

    // stack
    ListNode* approach1(ListNode* head)
    {
        if (!head)
            return nullptr;

        std::stack<ListNode*> stack;
        for (auto* i = head; i; i = i->next) {
            stack.push(i);
        }
        ListNode vHead(-1);
        auto* i = &vHead;
        while (!stack.empty()) {
            auto* next = stack.top()->next;
            stack.top()->next = nullptr;
            i->next = stack.top();
            i = i->next;
            stack.pop();
        }
        return vHead.next;
    }
};
