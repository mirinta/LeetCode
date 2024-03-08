#include <stack>

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
 * Given the head of a singly linked list, return true if it is a palindrome or false otherwise.
 *
 * ! The number of nodes in the list is in the range [1, 10^5].
 * ! 0 <= Node.val <= 9
 */

class Solution
{
public:
    bool isPalindrome(ListNode* head) { return approach2(head); }

private:
    // time O(N), space O(1)
    bool approach2(ListNode* head)
    {
        if (!head)
            return true;

        if (!head->next)
            return true; // only one node

        // length is even: X0 -> X1 -> X2 -> X3 ->NULL
        //                 | part1|    | part2|
        //  length is odd: X0 -> X1 -> X2 -> X3 -> X4 -> NULL
        //                 | part1|          | part2|
        auto* slow = head;
        auto* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        if (fast) {
            slow = slow->next; // length is odd
        }
        auto* forward = head;
        auto* backward = reverseLinkedList(slow);
        while (backward) {
            if (forward->val != backward->val)
                return false;

            forward = forward->next;
            backward = backward->next;
        }
        return true;
    }

    ListNode* reverseLinkedList(ListNode* head)
    {
        ListNode* prev = nullptr;
        while (head) {
            auto* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }

    // time O(N), space O(N)
    bool approach1(ListNode* head)
    {
        if (!head)
            return true;

        if (!head->next)
            return true; // only one node

        std::stack<ListNode*> stack;
        auto* node = head;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->next;
            }
            if (head->val != stack.top()->val)
                return false;

            head = head->next;
            stack.pop();
        }
        return true;
    }
};
