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
 * Given the "head" of a singly linked list, return "true" if it is a palindrome or "false"
 * otherwise.
 */

class Solution
{
public:
    // version 1: stack
    // bool isPalindrome(ListNode* head)
    // {
    //     if (!head)
    //         return false;

    //     std::stack<decltype(head->val)> stack;
    //     for (auto* iter = head; iter; iter = iter->next) {
    //         stack.push(iter->val);
    //     }
    //     for (auto* iter = head; iter && !stack.empty(); iter = iter->next) {
    //         if (iter->val != stack.top())
    //             return false;

    //         stack.pop();
    //     }
    //     return true;
    // }
    // ------------------------------
    // version 2: recursion
    //     bool isPalindrome(ListNode* head)
    //     {
    //         if (!head)
    //             return false;

    //         left = head;
    //         return checkPalindrome(head);
    //     }

    // private:
    //     ListNode* left = nullptr;
    //     bool checkPalindrome(ListNode* head)
    //     {
    //         if (!head)
    //             return true;

    //         const auto result = checkPalindrome(head->next) && (head->val == left->val);
    //         left = left->next;
    //         return result;
    //     }
    // ------------------------------
    // version 3: iteration
    bool isPalindrome(ListNode* head)
    {
        // step 1: find the middle node
        // - case 1 (even number): N0 -> N1 -> [N2] -> N3 -> NULL, N2 is the middle node
        // - case 2 (odd number): N0 -> N1 -> [N2] -> N3 -> N4 -> NULL, N2 is the middle node
        // step 2: reverse and compare
        // - case 1: compare (N0->N1) and reverse(N2->N3)
        // - case 2: compare (N0->N1) and reverse(N3->N4)
        auto* slow = head;
        auto* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        if (fast) {
            slow = slow->next; // for case 2
        }
        auto* forward = head;
        auto* backward = reverse(slow);
        while (backward) {
            if (forward->val != backward->val)
                return false;

            forward = forward->next;
            backward = backward->next;
        }
        return true;
    }

private:
    ListNode* reverse(ListNode* head)
    {
        ListNode* before = nullptr;
        auto* iter = head;
        while (iter) {
            auto* after = iter->next;
            iter->next = before;
            before = iter;
            iter = after;
        }
        return before;
    }
};