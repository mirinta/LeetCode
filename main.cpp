#include <iostream>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

size_t sum0toN(size_t n)
{
    std::cout << n << ", before base" << '\n';
    if (n == 0) {
        std::cout << n << ", reach base" << '\n';
        return 0;
    }
    std::cout << n << ", before recursion" << '\n';
    const auto result = n + sum0toN(n - 1);
    std::cout << n << ", after recursion" << '\n';
    return result;
}

void testRecursion()
{
    std::cout << "---begin---" << '\n';
    sum0toN(5);
    std::cout << "---end---" << '\n';
}

void printListForward(ListNode* head)
{
    if (!head) {
        std::cout << '\n';
        return;
    }

    std::cout << head->val;
    if (head->next) {
        std::cout << "->";
    }
    printListForward(head->next);
}

void printListBackward(ListNode* head)
{
    if (!head)
        return;

    printListBackward(head->next);
    std::cout << head->val << "->";
}

int main()
{
    ListNode n5{5};
    ListNode n4{n5.val - 1, &n5};
    ListNode n3{n4.val - 1, &n4};
    ListNode n2{n3.val - 1, &n3};
    ListNode n1{n2.val - 1, &n2};
    ListNode n0{n1.val - 1, &n1};

    printListForward(&n0);
    printListBackward(&n0);
}
