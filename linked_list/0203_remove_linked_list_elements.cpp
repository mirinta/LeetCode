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
 * Given the "head" of a linked list and an integer "val", remove all the nodes of the linked list
 * that has "Node.val == val", and return the new head.
 */

class Solution
{
public:
    ListNode* removeElements(ListNode* head, int val)
    {
        ListNode resultVHead{-1, head};
        auto* keep = &resultVHead;
        for (auto* iter = head; iter; iter = iter->next) {
            if (iter->val == val)
                continue;

            keep->next = iter;
            keep = keep->next;
        }
        keep->next = nullptr;
        return resultVHead.next;
    }
};