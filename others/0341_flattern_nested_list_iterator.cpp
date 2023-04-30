#include <list>
#include <vector>

/**
 * This is the interface that allows for creating nested lists.
 * ! You should not implement it, or speculate about its implementation
 */
class NestedInteger
{
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const std::vector<NestedInteger>& getList() const;
};

/**
 * You are given a nested list of integers "nestedList". Each element is either an integer or a list
 * whose elements may also be integers or other lists. Implement an interator to flatten it.
 *
 * Implement the "NestedIterator" class:
 *
 * - NestedIterator(List<NestedInteger> nestedList) Initializes the iterator with the nested list
 * nestedList.
 *
 * - int next() Returns the next integer in the nested list.
 *
 * - boolean hasNext() Returns true if there are still some integers in the nested list and false
 * otherwise.
 */

class NestedIterator
{
public:
    NestedIterator(std::vector<NestedInteger>& nestedList)
        : list(nestedList.begin(), nestedList.end())
    {
    }

    int next()
    {
        // call hasNext() first
        const int result = list.front().getInteger();
        list.pop_front();
        return result;
    }

    bool hasNext()
    {
        // if the first element is a list,
        // expand it and add all its elements at head of the list
        while (!list.empty() && !list.front().isInteger()) {
            const auto nestedList = list.front().getList();
            list.pop_front();
            for (long long i = nestedList.size() - 1; i >= 0; i--) {
                list.push_front(nestedList[i]);
            }
        }
        return !list.empty();
    }

private:
    std::list<NestedInteger> list; // constant time removal, more effective than vector
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
