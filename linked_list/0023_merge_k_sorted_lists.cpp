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
        if (lists.empty())
            return nullptr;

        auto greater = [](const auto* node1, const auto* node2) { return node1->val > node2->val; };
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(greater)> pq(greater);
        for (auto* node : lists) {
            if (node) {
                pq.push(node);
            }
        }
        ListNode vHead(-1);
        auto* i = &vHead;
        while (!pq.empty()) {
            auto* node = pq.top();
            pq.pop();
            i->next = node;
            if (node && node->next) {
                pq.push(node->next);
            }
            i = i->next;
        }
        return vHead.next;
    }
};
