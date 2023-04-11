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
 * Given the "head" of a linked list and a value "x", partition it such that all nodes less than "x"
 * come before nodes greater than or equal to "x".
 *
 * You should preserve the original relative order of the nodes in each of the two partitions.
 */
class Solution
{
public:
    // add top-level const to "head"
    ListNode* partition(ListNode* const head, int x)
    {
        auto* leVHead = new ListNode; // leVHead -> { nodes < x }
        auto* geVHead = new ListNode; // geVHead -> { nodes >= x }

        auto* iterLe = leVHead;
        auto* iterGe = geVHead;
        for (auto* iter = head; iter; iter = iter->next) {
            if (iter->val < x) {
                iterLe->next = iter;
                iterLe = iterLe->next;
            } else {
                iterGe->next = iter;
                iterGe = iterGe->next;
            }
        }
        // concate: leVHead -> {nodes < x} -> {nodes >= x} -> nullptr
        iterLe->next = geVHead->next;
        iterGe->next = nullptr;
        return leVHead->next;
    }
};
