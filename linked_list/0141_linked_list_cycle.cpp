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
 * Given "head", the head of a linked list, determine if the linked list has a cycle in it.
 *
 * Return "true" if there is a cycle in the linked list. Otherwise, return "false".
 */

class Solution
{
public:
    bool hasCycle(ListNode* head)
    {
        // version 1: hash map
        // std::unordered_map<ListNode*, int> map;
        // auto* iter = head;
        // while (iter) {
        //     if (map.find(iter) != map.end())
        //         return true;

        //     map[iter] = iter->val;
        //     iter = iter->next;
        // }
        // return false;
        // ------------------------------
        // version 2:
        auto* fast = head;
        auto* slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                return true;
        }
        return false;
    }
};
