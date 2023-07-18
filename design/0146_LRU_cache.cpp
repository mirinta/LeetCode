#include <unordered_map>

/**
 * Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.
 *
 * Implement the LRUCache class:
 *
 * - LRUCache(int capacity) initializes the LRU cache with positive size capacity.
 *
 * - int get(int key) returns the value of the key if the key exists, otherwise returns -1.
 *
 * - void put(int key, int value) updates the value of the key if the key exists. Otherwise, add the
 * key-value pair to the cache. If the number of keys exceeds the capacity from its operation, evict
 * the least recently used key.
 *
 * https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU
 *
 * ! The functions get and put must each run in O(1) average time complexity.
 */

struct Node
{
    int key;
    int val;
    Node* next;
    Node* prev;
    Node(int k, int v) : key(k), val(v), next(nullptr), prev(nullptr) {}
};

class DoubleList
{
public:
    explicit DoubleList() : m_head(new Node(-1, -1)), m_tail(new Node(-1, -1)), m_count(0)
    {
        m_head->next = m_tail;
        m_tail->prev = m_head;
    }

    int count() const { return m_count; }

    void pushFront(Node* n)
    {
        // before: m_head <-> P <-> ...
        //  after: m_head <-> n <-> P ...
        n->next = m_head->next;
        m_head->next->prev = n;
        m_head->next = n;
        n->prev = m_head;
        m_count++;
    }

    void pushBack(Node* n)
    {
        // before: ... <-> P <-> m_tail
        //  after: ... <-> P <-> n <-> m_tail
        m_tail->prev->next = n;
        n->prev = m_tail->prev;
        n->next = m_tail;
        m_tail->prev = n;
        m_count++;
    }

    void remove(Node* n)
    {
        if (!n)
            return;

        // before: ... <-> P <-> n <-> Q ...
        //  after: ... <-> P <-> Q ...
        n->prev->next = n->next;
        n->next->prev = n->prev;
        m_count--;
    }

    Node* popFront()
    {
        if (m_head->next == m_tail)
            return nullptr;

        // before: m_head <-> P <-> Q <-> ...
        //  after: m_head <-> Q <-> ...
        auto* p = m_head->next;
        remove(p);
        return p;
    }

    Node* popBack()
    {
        if (m_head->next == m_tail)
            return nullptr;

        // before: ... <-> P <-> Q <-> m_tail
        //  after: ... <-> P <-> m_tail
        auto* q = m_tail->prev;
        remove(q);
        return q;
    }

private:
    Node* m_head;
    Node* m_tail;
    int m_count;
};

class LRUCache
{
public:
    LRUCache(int capacity) : m_capacity(capacity) {}

    int get(int key)
    {
        if (!m_map.count(key))
            return -1;

        makeRecently(key);
        return m_map[key]->val;
    }

    void put(int key, int value)
    {
        if (m_map.count(key)) {
            m_map[key]->val = value;
            makeRecently(key);
            return;
        }
        if (m_cache.count() == m_capacity) {
            removeLeastRecently();
        }
        addRecently(key, value);
    }

private:
    void makeRecently(int key)
    {
        auto* n = m_map[key];
        m_cache.remove(n);
        m_cache.pushBack(n);
    }

    void addRecently(int key, int val)
    {
        auto* n = new Node(key, val);
        m_cache.pushBack(n);
        m_map[key] = n;
    }

    void deleteKey(int key)
    {
        auto* n = m_map[key];
        m_cache.remove(n);
        m_map.erase(key);
    }

    void removeLeastRecently()
    {
        auto* n = m_cache.popFront();
        m_map.erase(n->key);
    }

private:
    int m_capacity;
    std::unordered_map<int, Node*> m_map; // key to node
    DoubleList m_cache;
};

class LRUCache2
{
public:
    LRUCache2(int capacity) : _capacity(capacity) {}

    int get(int key)
    {
        if (!_map.count(key))
            return -1;

        makeRecently(key);
        return _lru.front().second;
    }

    void put(int key, int value)
    {
        if (_map.count(key)) {
            makeRecently(key);
            _lru.front().second = value;
            return;
        }
        if (_lru.size() == _capacity) {
            removeLeastRecently();
        }
        _lru.push_front({key, value});
        _map[key] = _lru.begin();
    }

private:
    void makeRecently(int key)
    {
        if (!_map.count(key))
            return;

        const int val = (*_map[key]).second;
        _lru.erase(_map[key]);
        _lru.push_front({key, val});
        _map[key] = _lru.begin();
    }

    void removeLeastRecently()
    {
        const int key = _lru.back().first;
        if (!_map.count(key))
            return;

        _map.erase(key);
        _lru.pop_back();
    }

private:
    int _capacity;
    // front() is the recently used "key-value"
    // back() is the least recently used "key-value"
    std::list<std::pair<int, int>> _lru;
    using Iter = std::list<std::pair<int, int>>::iterator;
    std::unordered_map<int, Iter> _map; // key to iterator
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
