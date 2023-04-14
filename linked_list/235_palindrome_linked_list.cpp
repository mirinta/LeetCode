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
    // version 1: stack, time complexity O(n), space complexity O(n)
    // bool isPalindrome(ListNode* head) {
    //     if (!head)
    //         return true;

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
    // version 2: recursion, time complexity O(n), space complexity O(n)
    // ListNode* left = nullptr;
    // bool isPalindrome(ListNode* head) {
    //     left = head;
    //     return checkPalindrome(head);
    // }

    // bool checkPalindrome(ListNode* head) {
    //     if (!head)
    //         return true;

    //     const auto result = checkPalindrome(head->next) && (head->val == left->val);
    //     left = left->next;
    //     return result;
    // }
    // version 3: time complexity O(n), space complexity O(1)
    bool isPalindrome(ListNode* head)
    {
        // step 1: find the middle node
        auto* slow = head;
        auto* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // case 1: even number
        // N0 -> N1 -> N2 -> N3 -> NULL
        //            slow         fast
        // reverse(slow)=reverse(N2->N3)=(N3->N2), then compare with (N0->N1)
        // case 2: odd number
        // N0 -> N1 -> N2 -> N3 -> N4 -> NULL
        //            slow        fast
        // reverse(slow->next)=reverse(N3->N4), then compare with (N0->N1)
        if (fast) {
            slow = slow->next;
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

    ListNode* reverse(ListNode* head)
    {
        ListNode* prev = nullptr;
        auto* iter = head;
        while (iter) {
            auto* next = iter->next;
            iter->next = prev;
            prev = iter;
            iter = next;
        }
        return prev;
    }
};