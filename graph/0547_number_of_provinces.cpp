#include <vector>

/**
 * There are "n" cities. Some of them are connected, while some are not. If city "a" is connected
 * directly with city "b", and city "b" is connected directly with city "c", then city "a" is
 * connected indirectly with city "c".
 *
 * A province is a group of directly or indirectly connected cities and no other cities outside of
 * the group.
 *
 * You are given an "n x n" matrix "isConnected" where isConnected[i][j] = 1 if the ith city and the
 * jth city are directly connected, and isConnected[i][j] otherwise.
 *
 * ! 1 <= n <= 200
 * ! n == isConnected.length
 * ! n == isConnected[i].length
 * ! isConnected[i][j] is 1 or 0.
 * ! isConnected[i][i] == 1
 * ! isConnected[i][j] == isConnected[j][i]
 */

class UnionFind
{
public:
    explicit UnionFind(int n) : _count(n), _parent(n, 0)
    {
        for (int i = 0; i < n; ++i) {
            _parent[i] = i;
        }
    }

    int count() const { return _count; }

    bool connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return false;

        _parent[rootQ] = rootP;
        _count--;
        return true;
    };

    int find(int x)
    {
        if (_parent[x] != x) {
            _parent[x] = find(_parent[x]);
        }
        return _parent[x];
    }

private:
    int _count;
    std::vector<int> _parent;
};

class Solution
{
public:
    int findCircleNum(const std::vector<std::vector<int>>& isConnected)
    {
        const auto n = isConnected.size();
        if (n <= 1)
            return n <= 0 ? 0 : 1;

        UnionFind uf(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (isConnected[i][j]) {
                    uf.connect(i, j);
                }
            }
        }
        return uf.count();
    }
};