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
 * Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving
 * only distinct numbers from the original list. Return the linked list sorted as well.
 *
 * ! The number of nodes in the list is in the range [0, 300].
 * ! -100 <= Node.val <= 100
 * ! The list is guaranteed to be sorted in ascending order.
 */

class Solution
{
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (!head)
            return nullptr;

        // sliding window, nodes in range [i,j)
        ListNode vHead(-1);
        auto* i = head;
        auto* k = &vHead;
        while (i) {
            auto* j = i;
            int count = 0;
            while (j && j->val == i->val) {
                j = j->next;
                count++;
            }
            if (count == 1) {
                k->next = i;
                i->next = nullptr;
                k = k->next;
            }
            i = j;
        }
        return vHead.next;
    }
};