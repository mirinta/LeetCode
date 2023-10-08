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
    // time O(N), space O(1)
    ListNode* approach2(ListNode* head)
    {
        if (!head)
            return nullptr;

        ListNode vHead(-1);
        vHead.next = head;
        auto* prev = &vHead;
        auto* curr = head;
        while (curr && curr->next) {
            auto* next = curr->next;
            curr->next = next->next;
            next->next = curr;
            prev->next = next;
            prev = curr;
            curr = curr->next;
        }
        return vHead.next;
    }

    // time O(N), space O(N)
    ListNode* approach1(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        // before: A->B->[...]
        //  after: B->A->[...]
        auto* newHead = head->next;
        head->next = approach1(head->next->next);
        newHead->next = head;
        return newHead;
    }
};
