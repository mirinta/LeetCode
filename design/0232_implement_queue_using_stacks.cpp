#include <stack>

/**
 * Implement a first in first out queue using only two stacks. The implemented queue should support
 * all the functions of a normal queue (push, peek, pop, and empty).
 *
 * Implement the MyQueue class:
 *
 * - void push(int x) pushes element x to the back of the queue.
 *
 * - int pop() removes the element from the front of the queue and returns it.
 *
 * - int peek() returns the element at the front of the queue.
 *
 * - boolean empty() returns true if the queue is empty, false otherwise.
 *
 * Notes:
 *
 * - You must use only standard operations of a stack, which means only push to top, peek/pop from
 * top, size, and is empty operations are valid.
 *
 * - Depending on your language, the stack may not be supported natively. You may simulate a stack
 * using a list or deque as long as you use only a stack's standard operations.
 */

class MyQueue
{
public:
    MyQueue() = default;

    void push(int x) { in.push(x); }

    int pop()
    {
        if (out.empty()) {
            for (; !in.empty(); in.pop()) {
                out.push(in.top());
            }
        }
        const auto val = out.top();
        out.pop();
        return val;
    }

    int peek()
    {
        const auto val = pop();
        out.push(val);
        return val;
    }

    bool empty() { return in.empty() && out.empty(); }

private:
    std::stack<int> in;
    std::stack<int> out;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
