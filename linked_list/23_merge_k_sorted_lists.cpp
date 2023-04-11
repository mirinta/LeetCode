#include <vector>
#include <queue>

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
 * You are given an array of "k" linked-lists "lists", each linked-list is sorted in ascending
 * order.
 *
 * Merge all the linked-lists into one sorted linked-list and return it.
 */

class Solution
{
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists)
    {
        auto* resultVHead = new ListNode;
        auto greater = [](ListNode* n1, ListNode* n2) { return n1->val > n2->val; };
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(greater)> queue(greater);
        for (auto* const head : lists) {
            if (head) {
                queue.push(head);
            }
        }
        auto* iter = resultVHead;
        while (!queue.empty()) {
            auto* node = queue.top();
            queue.pop();
            iter->next = node;
            if (node->next) {
                queue.push(node->next);
            }
            iter = iter->next;
        }
        return resultVHead->next;
    }
};
