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

        auto* slow = head;
        auto* fast = head;
        bool hasCycle = false;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }
        if (!hasCycle)
            return nullptr;

        // both slow and fast start at O,
        // cycle begins at X,
        // slow and fast meet at A
        // O->...->X->...->A
        //         |<-...<-|
        // moving distance of slow = D
        // moving distance of fast = 2D
        // 2D = OX + XA + AX + XA (1)
        //  D = OX + XA (2)
        // (1)-(2): D = AX + XA (3)
        // (2)-(3): OX = AX
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
