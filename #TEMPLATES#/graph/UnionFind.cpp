#include <vector>

class UnionFind
{
public:
    explicit UnionFind(int n) : count(n), root(n), size(n, 1)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int numOfConnectedComponents() const { return count; }

    /**
     * @note x is 0-indexed.
     */
    void reset(int x)
    {
        root[x] = x;
        size[x] = 1;
        count++;
    }

    /**
     * @note x is 0-indexed.
     */
    int find(int x)
    {
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    /**
     * @note p and q are 0-indexed.
     */
    bool isConnected(int p, int q) { return find(p) == find(q); }

    /**
     * @note p and q are 0-indexed.
     */
    void connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (size[rootQ] > size[rootP]) {
            root[rootP] = rootQ;
            size[rootQ] += size[rootP];
        } else {
            root[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
        count--;
    }

private:
    int count;
    std::vector<int> root;
    std::vector<int> size;
};