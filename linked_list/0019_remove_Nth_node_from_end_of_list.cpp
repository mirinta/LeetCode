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
 * Given the "head" of a linked list, remove the "nth" node from the end of the list and return its
 * "head".
 *
 * ! The number of nodes in the list is sz.
 * ! 1 <= sz <= 30
 * ! 0 <= Node.val <= 100
 * ! 1 <= n <= sz
 */

class Solution
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        if (!head)
            return nullptr;

        ListNode vHead(-1);
        vHead.next = head;
        auto* prev = getKthNodeFromEnd(&vHead, n + 1);
        prev->next = prev->next->next;
        return vHead.next;
    }

private:
    ListNode* getKthNodeFromEnd(ListNode* head, int k)
    {
        // 0->1->...->n-k->n-k+1->...->n-1->NULL
        // |<----n-k--->|  |<-------n-k------->|
        auto* fast = head;
        for (int i = 0; i < k; ++i) {
            fast = fast->next;
        }
        auto* slow = head;
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};
