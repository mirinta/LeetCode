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
 * Given the "head" of a linked list, return the node where the cycle begins. If there is no cycle,
 * return "nullptr".
 *
 * Do not modify the linked list.
 */

class Solution
{
public:
    ListNode* detectCycle(ListNode* const head)
    {
        auto* slow = head;
        auto* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                break;
        }
        if (!fast || !fast->next)
            return nullptr;

        slow = head;
        while (slow != fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};
