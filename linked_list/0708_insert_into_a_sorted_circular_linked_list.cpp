/**
 * Definition for a Node.
 *
 */
class Node
{
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val)
    {
        val = _val;
        next = nullptr;
    }

    Node(int _val, Node* _next)
    {
        val = _val;
        next = _next;
    }
};

/**
 * Given a Circular Linked List node, which is sorted in non-descending order, write a function to
 * insert a value "insertVal" into the list such that it remains a sorted circular list.
 *
 * The given node can be a reference to any single node in the list and may not necessarily be the
 * smallest value in the circular list.
 *
 * If there are multiple suitable places for insertion, you may choose any place to insert the new
 * value. After the insertion, the circular list should remain sorted.
 *
 * If the list is empty (i.e., the given node is null), you should create a new single circular list
 * and return the reference to that single node. Otherwise, you should return the originally given
 * node.
 *
 */

class Solution
{
public:
    Node* insert(Node* head, int insertVal)
    {
        if (!head) {
            auto* head = new Node(insertVal);
            head->next = head;
            return head;
        }
        // step 1: find min and max node
        // - [1]->2->[3], [3]->3->[3], [1]->1->[3]
        // - if there're duplicate max values, we want the last one
        // - if there're duplicate min values, we want the first one
        auto* min = head;
        auto* max = head;
        auto* p = head->next;
        while (p != head) {
            if (p->val < min->val) {
                min = p;
            } else if (p->val >= max->val) {
                max = p;
            }
            p = p->next;
        }
        // step 2: insertVal < min or insertVal > max
        if (insertVal < min->val || insertVal > max->val) {
            auto* node = new Node(insertVal, min);
            max->next = node;
            return head;
        }
        // step 3: insertVal in [min, max]
        p = min;
        while (true) {
            if (p->val <= insertVal && insertVal <= p->next->val) {
                auto* node = new Node(insertVal, p->next);
                p->next = node;
                break;
            }
            p = p->next;
        }
        return head;
    }
};