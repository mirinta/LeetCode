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
 * Given a linked list, swap every two adjacent nodes and return its head. You must solve the
 * problem without modifying the values in the lits's nodes (i.e., only nodes themselves may be
 * changed.)
 *
 */

class Solution
{
public:
    ListNode* swapPairs(ListNode* head)
    {
        // approach 1: iteration
        // - from: ... -> before -> (iter -> after) -> TAIL...
        // - to: ... -> before -> (after -> iter) -> TAIL...
        // - boundary: swap two adjacent nodes, i.e., iter and iter->next are not nullptr
        ListNode vHead{-1, head};
        auto* before = &vHead;
        auto* iter = head;
        while (iter && iter->next) {
            auto* after = iter->next;
            iter->next = after->next;
            after->next = iter;
            before->next = after;
            before = iter;
            iter = iter->next;
        }
        return vHead.next;
        // ------------------------------
        // approach 2: recursion
        // from: ... -> Ni -> N(i+1) -> swapPairs(N(i+2)->TAIL...)
        // to: ... -> N(i+1) -> Ni -> swapPairs(N(i+2)->TAIL...)
        // if (!head || !head->next)
        //     return head;

        // auto* newHead = head->next;
        // head->next = swapPairs(newHead->next);
        // newHead->next = head;
        // return newHead;
    }
};