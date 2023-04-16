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
 * Given the "head" of a linked list, remove the "nth" node from the end of the list and return its
 * "head".
 */

class Solution
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        // get the (n+1)th node from the end, say it is x.
        // then x->next = x->next->next, problem solved.
        ListNode resultVHead{-1, head};
        auto* prevNode = getKthNodeFromEnd(&resultVHead, n + 1);
        prevNode->next = prevNode->next->next;
        return resultVHead.next;
    }

private:
    ListNode* getKthNodeFromEnd(ListNode* head, int k)
    {
        // Suppose length of the list is N,
        // then index of the kth node from end is N-k.
        // Let iter1 move from 0 to k-1, i.e. move k nodes from start.
        // For iter1, there are (N-1)-(k-1)+1=N-k+1 nodes to move to the end.
        // Put iter2 at 0 and move with iter1 at the same time,
        // when iter1 reaches the end, iter2 is at index (N-k+1)-1=N-k.
        auto* iter1 = head;
        for (int i = 0; i < k; ++i) {
            iter1 = iter1->next; // according to the constraints, 1<=k<=N
        }
        auto* iter2 = head;
        while (iter1) {
            iter1 = iter1->next;
            iter2 = iter2->next;
        }
        return iter2;
    }
};
