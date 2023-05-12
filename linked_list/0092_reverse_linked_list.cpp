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
 * Given the "head" of a singly linked list and two integers "left" and "right" where "left" <=
 * "right", reverse the nodes of the list from position "left" to position "right", and return the
 * reversed list.
 */

class Solution
{
public:
    // approach 1:
    ListNode* reverseBetween(ListNode* head, int left, int right)
    {
        ListNode resultVHead{-1, head};
        auto* beforeLeft = &resultVHead;
        for (int i = 0; i < left - 1; ++i) {
            beforeLeft = beforeLeft->next;
        }
        auto* iter = beforeLeft->next;
        for (int i = 0; i < right - left; ++i) {
            auto* afterIter = iter->next;
            iter->next = afterIter->next;
            afterIter->next = beforeLeft->next;
            beforeLeft->next = afterIter;
        }
        return resultVHead.next;
    }
    // approach 2:
    //     ListNode* reverseBetween(ListNode* head, int left, int right)
    //     {
    //         if (left == 1)
    //             return reverseFirstKNodes(head, right);
    //
    //         head->next = reverseBetween(head->next, left - 1, right - 1);
    //         return head;
    //     }
    //
    // private:
    //     ListNode* _successor = nullptr;
    //     ListNode* reverseFirstKNodes(ListNode* head, int k)
    //     {
    //         if (k == 1) {
    //             _successor = head->next;
    //             return head;
    //         }
    //         auto* newHead = reverseFirstKNodes(head->next, k - 1);
    //         head->next->next = head;
    //         head->next = _successor;
    //         return newHead;
    //     }
};
