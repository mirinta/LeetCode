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
 */

class RandomizedSet
{
private:
    std::vector<int> _nums;
    std::unordered_map<int, size_t> _valToIndex;

public:
    RandomizedSet() = default;

    bool insert(int val)
    {
        if (_valToIndex.count(val))
            return false;

        _valToIndex[val] = _nums.size();
        _nums.push_back(val);
        return true;
    }

    bool remove(int val)
    {
        if (!_valToIndex.count(val))
            return false;

        const auto idx = _valToIndex[val];
        _valToIndex[_nums.back()] = idx;
        std::swap(_nums[idx], _nums.back());
        _nums.pop_back();
        _valToIndex.erase(val);
        return true;
    }

    int getRandom() { return _nums[std::rand() % _nums.size()]; }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */