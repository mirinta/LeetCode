/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。
 *
 * ! 0 <= 链表长度 <= 1000
 *
 * ! 本题与LC 21相同。
 */

class Solution
{
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        if (!l1)
            return l2;

        if (!l2)
            return l1;

        if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }

private:
    ListNode* approach1(ListNode* l1, ListNode* l2)
    {
        if (!l1)
            return l2;

        if (!l2)
            return l1;

        ListNode vHead(-1);
        auto* current = &vHead;
        auto* p1 = l1;
        auto* p2 = l2;
        while (l1 || l2) {
            if (!l1) {
                current->next = l2;
                current = current->next;
                l2 = l2->next;
                continue;
            }
            if (!l2) {
                current->next = l1;
                current = current->next;
                l1 = l1->next;
                continue;
            }
            if (l1->val < l2->val) {
                current->next = l1;
                l1 = l1->next;
            } else {
                current->next = l2;
                l2 = l2->next;
            }
            current = current->next;
        }
        return vHead.next;
    }
};