#include <stack>
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
 * You are given the head of a linked list with n nodes.
 *
 * For each node in the list, find the value of the next greater node. That is, for each node, find
 * the value of the first node that is next to it and has a strictly larger value than it.
 *
 * Return an integer array answer where answer[i] is the value of the next greater node of the ith
 * node (1-indexed). If the ith node does not have a next greater node, set answer[i] = 0.
 *
 * ! The number of nodes in the list is n.
 * ! 1 <= n <= 10^4
 * ! 1 <= Node.val <= 10^9
 */

class Solution
{
public:
    std::vector<int> nextLargerNodes(ListNode* head)
    {
        if (!head)
            return {};

        std::vector<int> nums;
        for (auto* i = head; i; i = i->next) {
            nums.push_back(i->val);
        }
        const int n = nums.size();
        std::vector<int> result(n, 0);
        std::stack<int> stack;
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] >= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? 0 : nums[stack.top()];
            stack.push(i);
        }
        return result;
    }
};