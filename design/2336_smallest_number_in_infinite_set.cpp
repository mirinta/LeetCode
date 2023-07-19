#include <queue>
#include <unordered_set>

/**
 * You have a set which contains all positive integers [1, 2, 3, 4, 5, ...].
 *
 * Implement the SmallestInfiniteSet class:
 *
 * - SmallestInfiniteSet() Initializes the SmallestInfiniteSet object to contain all positive
 * integers.
 *
 * - int popSmallest() Removes and returns the smallest integer contained in the infinite set.
 *
 * - void addBack(int num) Adds a positive integer num back into the infinite set, if it is not
 * already in the infinite set.
 *
 * ! 1 <= num <= 1000
 * ! At most 1000 calls will be made in total to popSmallest and addBack.
 */

class SmallestInfiniteSet
{
public:
    SmallestInfiniteSet() : current(1) {}

    int popSmallest()
    {
        if (!pq.empty()) {
            const int val = pq.top();
            pq.pop();
            seen.erase(val);
            return val;
        }
        return current++;
    }

    void addBack(int num)
    {
        if (num >= current || seen.count(num))
            return;

        pq.push(num);
        seen.insert(num);
    }

private:
    int current;
    std::unordered_set<int> seen;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq; // min heap
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */