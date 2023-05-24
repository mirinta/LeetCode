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
 * You are given two non-empty linked lists representing two non-negative integers. The digits are
 * stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and
 * return the sum as a linked list.
 *
 * You make assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 * ! The number of nodes in each linked list is in the range [1, 100].
 * ! 0 <= Node.val <= 9
 * ! It is guaranteed that the list represents a number that does not have leading zeros.
 */

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        if (!l1 || !l2)
            return nullptr;

        auto* iter1 = l1;
        auto* iter2 = l2;
        int carry = 0;
        ListNode vHead(-1);
        auto* iter = &vHead;
        while (iter1 || iter2) {
            iter->next = compute(carry, iter1 ? iter1->val : 0, iter2 ? iter2->val : 0);
            iter1 = iter1 ? iter1->next : nullptr;
            iter2 = iter2 ? iter2->next : nullptr;
            iter = iter->next;
        }
        if (carry > 0) {
            iter->next = new ListNode(carry);
        }
        return vHead.next;
    }

private:
    ListNode* compute(int& carry, int v1, int v2)
    {
        const auto sum = v1 + v2 + carry;
        carry = sum / 10;
        return new ListNode(sum % 10);
    }
};