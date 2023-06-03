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
 * Given the "head" of a linked list, rotate the list to the right by k places.
 *
 * ! The number of nodes in the list is in the range [0, 500].
 * ! -100 <= Node.val <= 100
 * ! 0 <= k <= 2 * 109
 */

class Solution
{
public:
    ListNode* rotateRight(ListNode* head, int k)
    {
        if (!head || k <= 0)
            return head;

        // the actual moving distance is k % n, where n is the number of nodes
        // - if n = 3, k = 2, 0->[1]->2 => 1->2->0
        // - the new head is the kth node from the end of the original list
        // - the new tail is the (k+1)th node from the end of the original list
        // - also, we need to know the tail node of the original list
        auto* tail = head;
        int count = 1;
        while (tail && tail->next) {
            tail = tail->next;
            count++;
        }
        if (count == 1 || k % count == 0)
            return head;

        auto* newTail = head;
        for (int i = 0; i < count - (k % count + 1); ++i) {
            newTail = newTail->next;
        }
        auto* newHead = newTail->next;
        tail->next = head;
        newTail->next = nullptr;
        return newHead;
    }

private:
    ListNode* getKthNodeFromEnd(ListNode* head, int k)
    {
        auto* first = head;
        for (int i = 0; i < k; ++i) {
            first = first->next;
        }
        auto* second = head;
        while (first) {
            first = first->next;
            second = second->next;
        }
        return second;
    }
};
