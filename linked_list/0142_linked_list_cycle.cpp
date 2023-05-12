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
 * Given the "head" of a linked list, return the node where the cycle begins. If there is no cycle,
 * return "nullptr".
 *
 * Do not modify the linked list.
 */

class Solution
{
public:
    ListNode* detectCycle(ListNode* const head)
    {
        // approach 1: hash map
        // std::unordered_map<ListNode*, int> map;
        // for (auto* iter = head; iter; iter = iter->next) {
        //     if (map.find(iter) != map.end())
        //         return iter;

        //     map[iter] = iter->val;
        // }
        // return nullptr;
        // ------------------------------
        // approach 2:
        // Let iterA and iterB move from "head" at the same time,
        // speed of iterA = 2x speed of iterB.
        // Suppose the start point is O,
        // the cycle begins at A, and iterA and iterB meet at M.
        // O -> A -> M
        //      | <- |
        // When they meet each other, we have:
        // the moving distance of iterB = D = OA + AM (1)
        // the moving distance of iterA = 2D = OA + AM + MA + AM (2)
        // Let (2) - (1): D = MA + AM (3)
        // Let (3) - (1): OA = MA (4)
        // Let iterA moves from M and iterB moves from O with the same speed,
        // this time they'll meet at M.
        auto* iterA = head;
        auto* iterB = head;
        while (iterA && iterA->next) {
            iterA = iterA->next->next;
            iterB = iterB->next;
            if (iterA == iterB)
                break;
        }
        if (!iterA || !iterA->next)
            return nullptr;

        iterB = head;
        while (iterA != iterB) {
            iterA = iterA->next;
            iterB = iterB->next;
        }
        return iterB;
    }
};
