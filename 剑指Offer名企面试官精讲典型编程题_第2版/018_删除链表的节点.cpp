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
 * 给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。
 *
 * 返回删除后的链表的头节点。
 *
 * ! 题目保证链表中节点的值互不相同
 * ! 若使用 C 或 C++ 语言，你不需要 free 或 delete 被删除的节点
 */