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
 * You are given the heads of two sorted linked lists "list1" and "list2".
 *
 * Merge the two lists in one sorted list. The list should be made by splicing together the nodes of
 * the first two lists.
 *
 * Return the head of the merged linked list.
 */

class Solution
{
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        if (!list1)
            return list2;

        if (!list2)
            return list1;

        ListNode vHead(-1);
        auto* current = &vHead;
        auto* p1 = list1;
        auto* p2 = list2;
        while (p1 || p2) {
            if (!p1) {
                current->next = p2;
                current = current->next;
                p2 = p2->next;
                continue;
            }
            if (!p2) {
                current->next = p1;
                current = current->next;
                p1 = p1->next;
                continue;
            }
            if (p1->val < p2->val) {
                current->next = p1;
                p1 = p1->next;
            } else {
                current->next = p2;
                p2 = p2->next;
            }
            current = current->next;
        }
        return vHead.next;
    }

private:
    ListNode* approach2(ListNode* list1, ListNode* list2)
    {
        // recursion, the original inputs are changed:
        if (!list1)
            return list2;

        if (!list2)
            return list1;

        if (list1->val < list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
};
