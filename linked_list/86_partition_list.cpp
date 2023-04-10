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
    ListNode* partition(ListNode* head, int x)
    {
        auto* vhead_le = new ListNode;
        auto* vhead_ge = new ListNode;
        auto* iter_le = vhead_le;
        auto* iter_ge = vhead_ge;
        while (head) {
            if (head->val < x) {
                iter_le->next = head;
                iter_le = iter_le->next;
            } else {
                iter_ge->next = head;
                iter_ge = iter_ge->next;
            }
            head = head->next;
        }
        iter_ge->next = nullptr;
        iter_le->next = vhead_ge->next;
        return vhead_le->next;
    }
};
