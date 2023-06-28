#include <algorithm>
#include <vector>

/**
 * There are n people in a social group labeled from 0 to n - 1. You are given an array logs where
 * logs[i] = [timestampi, xi, yi] indicates that xi and yi will be friends at the time timestampi.
 *
 * Friendship is symmetric. That means if a is friends with b, then b is friends with a. Also,
 * person a is acquainted with a person b if a is friends with b, or a is a friend of someone
 * acquainted with b.
 *
 * Return the earliest time for which every person became acquainted with every other person. If
 * there is no such earliest time, return -1.
 *
 * ! 2 <= n <= 100
 * ! 1 <= logs.length <= 10^4
 * ! logs[i].length == 3
 * ! 0 <= timestampi <= 10^9
 * ! 0 <= xi, yi <= n - 1
 * ! xi != yi
 * ! All the values timestampi are unique.
 * ! All the pairs (xi, yi) occur at most one time in the input.
 */

class UnionFind
{
public:
    explicit UnionFind(int n) : _root(n), _rank(n), _count(n)
    {
        for (int i = 0; i < n; ++i) {
            _root[i] = i;
            _rank[i] = 1;
        }
    }

    int count() const { return _count; }

    int find(int x)
    {
        if (x != _root[x]) {
            _root[x] = find(_root[x]);
        }
        return _root[x];
    }

    void connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (_rank[rootP] > _rank[rootQ]) {
            _root[rootQ] = rootP;
        } else if (_rank[rootP] < _rank[rootQ]) {
            _root[rootP] = rootQ;
        } else {
            _root[rootQ] = rootP;
            _rank[rootP] += 1;
        }
        _count -= 1;
    }

private:
    std::vector<int> _root;
    std::vector<int> _rank;
    int _count;
};

class Solution
{
public:
    int earliestAcq(std::vector<std::vector<int>>& logs, int n)
    {
        auto comp = [](const std::vector<int>& log1, const std::vector<int>& log2) -> bool {
            return log1[0] < log2[0];
        };
        std::sort(logs.begin(), logs.end(), comp);
        UnionFind uf(n);
        for (const auto& log : logs) {
            uf.connect(log[1], log[2]);
            if (uf.count() == 1)
                return log[0];
        }
        return -1;
    }
};