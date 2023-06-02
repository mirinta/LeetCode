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
 * Given the head of a singly linked list, group all the nodes with odd indices together followed by
 * the nodes with even indices, and return the reordered list.
 *
 * The first node is considered odd, and the second node is even, and so on.
 *
 * Note that the relative order inside both the even and odd groups should remain as it was in the
 * input.
 *
 * You must solve this problem in O(1) extra space complexity and O(n) time complexity.
 *
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    ListNode* oddEvenList(ListNode* head) { return oddEvenList_v1(head); }

private:
    ListNode* oddEvenList_v2(ListNode* head)
    {
        if (!head)
            return nullptr;

        auto* even = head;
        auto* odd = head->next;
        auto* oddHead = odd;
        while (odd && odd->next) {
            even->next = odd->next;
            even = even->next;
            odd->next = even->next;
            odd = odd->next;
        }
        even->next = oddHead;
        return head;
    }

    ListNode* oddEvenList_v1(ListNode* head)
    {
        if (!head)
            return nullptr;

        ListNode vHeadEven(-1);
        auto* even = &vHeadEven;
        ListNode vHeadOdd(-1);
        auto* odd = &vHeadOdd;
        auto* iter = head;
        for (int i = 0; iter; ++i) {
            if (i % 2 == 0) {
                even->next = iter;
                even = even->next;
            } else {
                odd->next = iter;
                odd = odd->next;
            }
            iter = iter->next;
        }
        even->next = vHeadOdd.next;
        odd->next = nullptr;
        return vHeadEven.next;
    }
};