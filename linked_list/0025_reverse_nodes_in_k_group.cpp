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
 *
 * ! The number of nodes in the list is n.
 * ! 1 <= k <= n <= 5000
 * ! 0 <= Node.val <= 1000
 */

class Solution
{
public:
    ListNode* reverseKGroup(ListNode* head, int k)
    {
        if (!head)
            return nullptr;

        auto* newTail = head;
        auto* afterNewTail = head;
        for (int i = 0; i < k; ++i) {
            if (!afterNewTail)
                return head; // not enough nodes, remain as it is

            afterNewTail = afterNewTail->next;
        }
        auto* newHead = reverseBetween(head, afterNewTail);
        newTail->next = reverseKGroup(afterNewTail, k);
        return newHead;
    }

private:
    // ...->[1->...->k]->k+1 => ...->[k->...->1]->k+1
    // reverse nodes in range [node1,nodeK+1)
    ListNode* reverseBetween(ListNode* node1, ListNode* nodeKPlus1)
    {
        ListNode* prev = nullptr;
        auto* current = node1;
        while (current != nodeKPlus1) {
            auto* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        return prev;
    }
};