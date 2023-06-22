#include <stack>

/**
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 *
 * Implement the MinStack class:
 *
 * - MinStack() initializes the stack object.
 *
 * - void push(int val) pushes the element val onto the stack.
 *
 * - void pop() removes the element on the top of the stack.
 *
 * - int top() gets the top element of the stack.
 *
 * - int getMin() retrieves the minimum element in the stack.
 *
 * You must implement a solution with O(1) time complexity for each function.
 *
 *
 * ! -2^31 <= val <= 2^31 - 1
 * ! Methods pop, top and getMin operations will always be called on non-empty stacks.
 * ! At most 3 * 10^4 calls will be made to push, pop, top, and getMin.
 */

class MinStack
{
public:
    MinStack() {}

    void push(int val)
    {
        _data.push(val);
        if (_min.empty() || val < _min.top()) {
            _min.push(val);
        } else {
            _min.push(getMin());
        }
    }

    void pop()
    {
        if (_data.empty() || _min.empty())
            return;

        _data.pop();
        _min.pop();
    }

    int top() { return _data.top(); }

    int getMin() { return _min.top(); }

private:
    std::stack<int> _data;
    std::stack<int> _min;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */