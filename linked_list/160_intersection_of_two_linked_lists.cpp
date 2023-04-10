#include <unordered_map>

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
 */

class Solution
{
public:
    ListNode* getIntersectionNode(ListNode* const headA, ListNode* const headB)
    {
        if (!headA || !headB)
            return nullptr;

        auto* iter_a = headA;
        auto* iter_b = headB;
        while (iter_a != iter_b) {
            iter_a = iter_a ? iter_a->next : headB;
            iter_b = iter_b ? iter_b->next : headA;
        }
        return iter_a;
        // using hash map:
        //    if (!headA || !headB)
        //        return nullptr;
        //
        //    std::unordered_map<ListNode*, int> map;
        //    for (auto* i = headA; i; i = i->next) {
        //        map[i] = i->val;
        //    }
        //    for (auto* j = headB; j; j = j->next) {
        //        if (map.find(j) != map.end())
        //            return j;
        //    }
        //    return nullptr;
    }
};
