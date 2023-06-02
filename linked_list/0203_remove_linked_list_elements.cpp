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
        // return removeElements_v2(head, val);
        return removeElements_v1(head, val);
    }

private:
    ListNode* removeElements_v1(ListNode* head, int val)
    {
        if (!head)
            return nullptr;

        auto* node = removeElements(head->next, val);
        if (head->val == val)
            return node;

        head->next = node;
        return head;
    }

    ListNode* removeElements_v2(ListNode* head, int val)
    {
        if (!head)
            return nullptr;

        ListNode virtualHead(-1);
        auto* current = &virtualHead;
        for (auto* i = head; i; i = i->next) {
            if (i->val == val)
                continue;

            current->next = i;
            current = current->next;
        }
        current->next = nullptr; // this is important
        return virtualHead.next;
    }
};