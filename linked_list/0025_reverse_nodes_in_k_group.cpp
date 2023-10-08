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

        // before: p0->[n1->...->nk]->nk+1
        //  after: ->[nk->...->n1]->nk+1, n1 becomes p0
        int n = numOfNodes(head);
        ListNode vHead(-1);
        vHead.next = head;
        auto* p0 = &vHead;
        ListNode* prev = nullptr;
        auto* curr = head;
        while (n >= k) {
            n -= k;
            for (int i = 0; i < k; ++i) {
                auto* next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            } // when the loop ends, prev = nk, curr = nk+1
            auto* next = p0->next;
            p0->next->next = curr;
            p0->next = prev;
            p0 = next;
        }
        return vHead.next;
    }

private:
    int numOfNodes(ListNode* head)
    {
        if (!head)
            return 0;

        int result = 0;
        while (head) {
            result++;
            head = head->next;
        }
        return result;
    }
};
