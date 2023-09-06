#include <random>
#include <unordered_map>
#include <vector>

/**
 * Implement the "RandomizedSet" class:
 *
 * - "RandomizedSet()" initializes the "RandomizedSet" object.
 *
 * - "bool insert(int val)" inserts an item "val" into the set if not present. Returns "true" if the
 * item was not present, "false" otherwise.
 *
 * - "bool remove(int val)" removes an item "val" from the set if present. Returns "true" if the
 * item was present, "false" otherwise.
 *
 * - "int getRandom()" returns a random element from the current set of elements (it's guaranteed
 * that at least one element exists when this method is called). Each element must have the same
 * probability of being returned.
 *
 * ! You must implement the functions of the class such that each function works in average O(1)
 * ! time complexity.
 *
 * ! -2^31 <= val <= 2^31 - 1
 * ! At most 2 * 10^5 calls will be made to insert, remove, and getRandom.
 * ! There will be at least one element in the data structure when getRandom is called.
 */

class RandomizedSet
{
public:
    RandomizedSet()
    {
        std::random_device rd;
        gen = std::mt19937(rd());
    }

    bool insert(int val)
    {
        if (valToIndex.count(val))
            return false;

        data.push_back(val);
        valToIndex[val] = data.size() - 1;
        return true;
    }

    bool remove(int val)
    {
        if (!valToIndex.count(val))
            return false;

        valToIndex[data.back()] = valToIndex[val];
        std::swap(data.back(), data[valToIndex[val]]);
        data.pop_back();
        valToIndex.erase(val);
        return true;
    }

    int getRandom()
    {
        std::uniform_int_distribution<int> dist(0, data.size() - 1);
        return data[dist(gen)];
    }

private:
    std::vector<int> data;
    std::unordered_map<int, int> valToIndex;
    std::mt19937 gen;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */