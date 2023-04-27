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
        // version 1:
        // ListNode vHead{-1, nullptr};
        // auto* iter1 = list1;
        // auto* iter2 = list2;
        // auto* merge = &vHead;
        // while (iter1 && iter2) {
        //     if (iter1->val < iter2->val) {
        //         merge->next = iter1;
        //         iter1 = iter1->next;
        //     } else {
        //         merge->next = iter2;
        //         iter2 = iter2->next;
        //     }
        //     merge = merge->next;
        // }
        // if (iter1 && !iter2) {
        //     merge->next = iter1;
        // }
        // if (!iter1 && iter2) {
        //     merge->next = iter2;
        // }
        // return vHead.next;
        // ------------------------------
        // version 2: recursion
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