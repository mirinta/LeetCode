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
    ListNode* swapPairs(ListNode* head) { return approach2(head); }

private:
    // iteration
    ListNode* approach2(ListNode* head)
    {
        // Before->[i]->After->{X X X} => Before->After->[i]->{X X X}
        if (!head)
            return nullptr;

        ListNode vHead(-1);
        vHead.next = head;
        auto* before = &vHead;
        auto* i = head;
        while (i && i->next) {
            auto* after = i->next;
            i->next = after->next;
            after->next = i;
            before->next = after;
            before = i;
            i = i->next;
        }
        return vHead.next;
    }

    // recursion
    ListNode* approach1(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        // [A->B]->{X X X} => [B->A]->{X X X}
        auto* newHead = head->next;
        head->next = approach1(newHead->next);
        newHead->next = head;
        return newHead;
    }
};