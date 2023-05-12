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
        // approach 1: hash map
        // std::unordered_map<ListNode*, int> map;
        // for(auto* iterA = headA; iterA; iterA = iterA->next) {
        //     map[iterA] = iterA->val;
        // }
        // for (auto* iterB = headB; iterB; iterB = iterB->next) {
        //     if (map.find(iterB) != map.end())
        //         return iterB;

        //     map[iterB] = iterB->val;
        // }
        // return nullptr;
        // ------------------------------
        // approach 2:
        auto* iterA = headA;
        auto* iterB = headB;
        while (iterA != iterB) {
            iterA = iterA ? iterA->next : headB;
            iterB = iterB ? iterB->next : headA;
        }
        return iterA;
    }
};
