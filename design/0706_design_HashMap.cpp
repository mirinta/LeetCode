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
    MyHashMap() : data(k_base) {}

    void put(int key, int value)
    {
        const int h = hash(key);
        for (auto iter = data[h].begin(); iter != data[h].end(); ++iter) {
            if (iter->first == key) {
                iter->second = value;
                return;
            }
        }
        data[h].emplace_back(key, value);
    }

    int get(int key)
    {
        const int h = hash(key);
        for (auto iter = data[h].begin(); iter != data[h].end(); ++iter) {
            if (iter->first == key)
                return iter->second;
        }
        return -1;
    }

    void remove(int key)
    {
        const int h = hash(key);
        for (auto iter = data[h].begin(); iter != data[h].end(); ++iter) {
            if (iter->first == key) {
                data[h].erase(iter);
                return;
            }
        }
    }

private:
    static int hash(int key) { return key % k_base; }

private:
    static constexpr int k_base = 2048;
    std::vector<std::list<std::pair<int, int>>> data;
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
