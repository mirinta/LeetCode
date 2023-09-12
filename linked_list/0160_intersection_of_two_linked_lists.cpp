#include <unordered_set>

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
 * Given the heads of two singly linked-lists "headA" and "headB", return the node at which the two
 * lists intersect. If the two linked lists have no intersection at all, return "nullptr".
 *
 * The test cases are generated such that there are no cycles anywhere in the entire linked
 * structure.
 *
 * Note that the linked lists must retain their original structure after the function returns.
 *
 * ! The number of nodes of listA is in the m.
 * ! The number of nodes of listB is in the n.
 * ! 1 <= m, n <= 3 * 10^4
 * ! 1 <= Node.val <= 10^5
 * ! 0 <= skipA < m
 * ! 0 <= skipB < n
 * ! intersectVal is 0 if listA and listB do not intersect.
 * ! intersectVal == listA[skipA] == listB[skipB] if listA and listB intersect.
 */

class Solution
{
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
        return approach2(headA, headB);
    }

private:
    ListNode* approach2(ListNode* headA, ListNode* headB)
    {
        if (!headA || !headB)
            return nullptr;

        auto* iterA = headA;
        auto* iterB = headB;
        while (iterA != iterB) {
            iterA = iterA ? iterA->next : headB;
            iterB = iterB ? iterB->next : headA;
        }
        return iterA;
    }

    ListNode* approach1(ListNode* headA, ListNode* headB)
    {
        if (!headA || !headB)
            return nullptr;

        std::unordered_set<ListNode*> set;
        while (headA) {
            set.insert(headA);
            headA = headA->next;
        }
        while (headB) {
            if (set.count(headB))
                return headB;

            headB = headB->next;
        }
        return nullptr;
    }
};
