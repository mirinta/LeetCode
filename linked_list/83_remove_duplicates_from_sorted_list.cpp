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
 * Given the "head" of a sorted linked list, delete all duplicates such that each element appears
 * only once.
 *
 * Return the linked list sorted as well.
 */

class Solution
{
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (!head)
            return nullptr;

        auto* keep = head;
        for (auto* iter = head; iter; iter = iter->next) {
            if (iter->val != keep->val) {
                keep->next = iter;
                keep = keep->next;
            }
        }
        keep->next = nullptr;
        return head;
    }
};