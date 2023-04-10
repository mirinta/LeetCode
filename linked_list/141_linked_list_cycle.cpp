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
 * Given "head", the head of a linked list, determine if the linked list has a cycle in it.
 *
 * Return "true" if there is a cycle in the linked list. Otherwise, return "false".
 */

class Solution
{
public:
    bool hasCycle(ListNode* head)
    {
        auto* slow = head; // 1x speed
        auto* fast = head; // 2x speed
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        return false;
    }
};
