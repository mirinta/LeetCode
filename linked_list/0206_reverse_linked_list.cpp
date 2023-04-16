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
 */

class Solution
{
public:
    ListNode* reverseList(ListNode* head)
    {
        // version 1: iteration
        ListNode* prev = nullptr;
        auto* iter = head;
        while (iter) {
            auto* next = iter->next;
            iter->next = prev;
            prev = iter;
            iter = next;
        }
        return prev;
        // version 2: recursion
        // 1. N0 -> reverseList(N1 -> ... -> Nm)
        // 2. N0 -> (N1 <- ... <- Nm), Nm is the head of the reversed sub-list
        // 3. Set N0->next->next = N0 and N0->next = nullptr;
        // if (!head || !head->next)
        //     return head;

        // auto* newHead = reverseList(head->next);
        // head->next->next = head;
        // head->next = nullptr;
        // return newHead;
        // ------------------------------
        // version 3: stack
        // std::stack<ListNode*> stack;
        // auto* iter = head;
        // while (iter) {
        //     stack.push(iter);
        //     auto* temp = iter;
        //     iter = iter->next;
        //     temp->next = nullptr;
        // }
        // ListNode resultVHead{};
        // iter = &resultVHead;
        // while (!stack.empty()) {
        //     iter->next = stack.top();
        //     iter = iter->next;
        //     stack.pop();
        // }
        // return resultVHead.next;
    }
};
