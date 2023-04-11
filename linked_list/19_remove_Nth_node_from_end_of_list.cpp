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
 * Given the "head" of a linked list, remove the "nth" node from the end of the list and return its
 * "head".
 */

class Solution
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        auto* resultVHead = new ListNode{-1, head};
        auto* iterA = resultVHead;
        for (int i = 0; i < n; ++i) {
            iterA = iterA->next;
        }
        auto* iterB = resultVHead;
        for (; iterA->next; iterA = iterA->next) {
            iterB = iterB->next;
        }
        iterB->next = iterB->next->next;
        return resultVHead->next;
    }
};
