#include <unordered_map>
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
 * Given the "head" of a singly linked list, return the "middle" node of the linked list.
 *
 * If there are two middle nodes, return the second middle node;
 */

class Solution
{
public:
    ListNode* middleNode(ListNode* head)
    {
        // version 1: hash map
        // std::unordered_map<int, ListNode*> map;
        // auto* iter = head;
        // for (int i = 0; iter; iter = iter->next, ++i) {
        //     map[i] = iter;
        // }
        // return map[map.size() / 2];
        // ------------------------------
        // version 2: double pointers
        auto* slow = head;
        auto* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
};
