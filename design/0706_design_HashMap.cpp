#include <list>
#include <vector>

/**
 * Design a HashMap without using any built-in hash table libraries.
 *
 * Implement the MyHashMap class:
 *
 * - MyHashMap() initializes the object with an empty map.
 *
 * - void put(int key, int value) inserts a (key, value) pair into the HashMap. If the key already
 * exists in the map, update the corresponding value.
 *
 * - int get(int key) returns the value to which the specified key is mapped, or -1 if this map
 * contains no mapping for the key.
 *
 * - void remove(key) removes the key and its corresponding value if the map contains the mapping
 * for the key.
 *
 * ! 0 <= key, value <= 106
 * ! At most 104 calls will be made to put, get, and remove.
 */

class MyHashMap
{
public:
    MyHashMap() : _buckets(k_size, std::list<std::pair<int, int>>{}) {}

    void put(int key, int value)
    {
        auto& bucket = getBucket(key);
        auto iter = find(key);
        if (iter != bucket.end()) {
            (*iter).second = value;
        } else {
            bucket.emplace_back(key, value);
        }
    }

    int get(int key)
    {
        const auto& bucket = getBucket(key);
        auto iter = find(key);
        if (iter != bucket.end())
            return (*iter).second;

        return -1;
    }

    void remove(int key)
    {
        auto& bucket = getBucket(key);
        auto iter = find(key);
        if (iter != bucket.end()) {
            bucket.erase(iter);
        }
    }

private:
    std::list<std::pair<int, int>>::iterator find(int key)
    {
        auto& bucket = getBucket(key);
        return std::find_if(bucket.begin(), bucket.end(),
                            [&key](const auto& pair) { return pair.first == key; });
    }

    std::list<std::pair<int, int>>& getBucket(int key) { return _buckets[key % k_size]; }

private:
    static constexpr size_t k_size = 2048;
    std::vector<std::list<std::pair<int, int>>> _buckets;
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
