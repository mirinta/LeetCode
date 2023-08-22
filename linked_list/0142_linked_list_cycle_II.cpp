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
 *
 * ! The number of the nodes in the list is in the range [0, 10^4].
 * ! -10^5 <= Node.val <= 10^5
 * ! pos is -1 or a valid index in the linked-list.
 */

class Solution
{
public:
    ListNode* detectCycle(ListNode* head)
    {
        if (!head)
            return nullptr;

        // start from O, cycle at X, meet at A
        // O ... X---->A
        //       |<----|
        // moving distance: fast = 2D = OX + XA + AX + XA (1)
        // moving distance: slow = D = OX + XA (2)
        // (1)-(2): D = AX + XA (3)
        // (3)-(2): AX = OX
        auto* slow = head;
        auto* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                break;
        }
        // no cycle
        if (!fast || !fast->next)
            return nullptr;

        slow = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};
