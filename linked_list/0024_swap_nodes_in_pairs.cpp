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
 * ! The number of nodes in the list is in the range [0, 100].
 * ! 0 <= Node.val <= 100
 */

class Solution
{
public:
    ListNode* swapPairs(ListNode* head) { return approach2(head); }

private:
    // Iteration
    ListNode* approach2(ListNode* head)
    {
        // prev_i->[i]->next_i->{X...X} => prev_i->next_i->[i]->{X...X}
        if (!head)
            return nullptr;

        ListNode vHead(-1);
        vHead.next = head;
        auto* prev = &vHead;
        auto* i = head;
        while (i && i->next) {
            auto* next = i->next;
            i->next = next->next;
            next->next = i;
            prev->next = next;
            prev = i;
            i = i->next;
        }
        return vHead.next;
    }

    // Recursion
    ListNode* approach1(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        // A->B->{X...X} => B->A->{X...X}
        auto* newHead = head->next;
        head->next = approach1(newHead->next);
        newHead->next = head;
        return newHead;
    }
};
