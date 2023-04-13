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
 * Given the "head" of a linked list, reverse the nodes of the list "k" at a time, and return the
 * modified list.
 *
 * "k" is a positive integer and is less than or equal to the length of the linked list. If the
 * number of nodes is not a multiple of "k" then left-out nodes, in the end, should remain as it is.
 *
 * You may not alter the values in the list's nodes, only nodes themselves may be changed.
 */

class Solution
{
public:
    ListNode* reverseKGroup(ListNode* head, int k)
    {
        if (!head)
            return head;

        auto* a = head;
        auto* b = head;
        for (int i = 0; i < k; ++i) {
            if (!b)
                return head;

            b = b->next;
        }
        auto* newHead = reverseBetween(a, b);
        a->next = reverseKGroup(b, k);
        return newHead;
    }

private:
    // reverse nodes in [a, b)
    ListNode* reverseBetween(ListNode* a, ListNode* b)
    {
        // from ->(Na->...->Nb-1)->Nb to <-Na<-...<-Nb-1 Nb
        ListNode* prev = nullptr;
        auto* iter = a;
        auto* next = a;
        while (iter != b) {
            next = iter->next;
            iter->next = prev;
            prev = iter;
            iter = next;
        }
        return prev;
    }
};
