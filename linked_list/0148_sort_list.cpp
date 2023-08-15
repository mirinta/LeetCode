#include <algorithm>
#include <vector>

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
 * Given the head of a linked list, return the list after sorting it in ascending order.
 *
 * ! The number of nodes in the list is in the range [0, 5 * 10^4].
 * ! -10^5 <= Node.val <= 10^5
 */

class Solution
{
public:
    ListNode* sortList(ListNode* head) { return approach2(head); }

private:
    // time O(NlogN), space O(logN)
    ListNode* approach2(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        // HEAD->...->MID->MID+1->...->TAIL
        auto* slow = head;
        auto* fast = head;
        ListNode* prev = nullptr;
        while (fast && fast->next) {
            prev = slow;
            fast = fast->next->next;
            slow = slow->next;
        }
        prev->next = nullptr;
        auto* sortedLeft = approach2(head);
        auto* sortedRight = approach2(slow);
        return mergeSortedLinkedLists(sortedLeft, sortedRight);
    }

    ListNode* mergeSortedLinkedLists(ListNode* head1, ListNode* head2)
    {
        ListNode vHead(-1);
        auto* node = &vHead;
        while (head1 || head2) {
            if (!head1) {
                node->next = head2;
                head2 = head2->next;
            } else if (!head2) {
                node->next = head1;
                head1 = head1->next;
            } else if (head1->val < head2->val) {
                node->next = head1;
                head1 = head1->next;
            } else {
                node->next = head2;
                head2 = head2->next;
            }
            node = node->next;
        }
        return vHead.next;
    }

    // time O(NlogN), space O(N)
    ListNode* approach1(ListNode* head)
    {
        if (!head)
            return nullptr;

        std::vector<ListNode*> nodes;
        for (auto node = head; node; node = node->next) {
            nodes.push_back(node);
        }
        std::sort(nodes.begin(), nodes.end(), [](const auto* const node1, const auto* const node2) {
            return node1->val < node2->val;
        });
        for (int i = 0; i < nodes.size() - 1; ++i) {
            nodes[i]->next = nodes[i + 1];
        }
        nodes.back()->next = nullptr;
        return nodes.front();
    }
};