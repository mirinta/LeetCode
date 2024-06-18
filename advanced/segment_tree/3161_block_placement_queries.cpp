#include <set>
#include <vector>

/**
 * There exists an infinite number line, with its origin at 0 and extending towards the positive
 * x-axis.
 *
 * You are given a 2D array queries, which contains two types of queries:
 *
 * 1. For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin.
 * It is guaranteed that there is no obstacle at distance x when the query is asked.
 *
 * 2. For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of
 * size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range
 * [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note
 * that you do not actually place the block. Queries are separate.
 *
 * Return a boolean array results, where results[i] is true if you can place the block specified in
 * the ith query of type 2, and false otherwise.
 *
 * ! 1 <= queries.length <= 15 * 10^4
 * ! 2 <= queries[i].length <= 3
 * ! 1 <= queries[i][0] <= 2
 * ! 1 <= x, sz <= min(5 * 10^4, 3 * queries.length)
 * ! The input is generated such that for queries of type 1, no obstacle exists at distance x when
 * ! the query is asked.
 * ! The input is generated such that there is at least one query of type 2.
 */

class SegmentTree
{
public:
    explicit SegmentTree(long long n) : data(4 * n, 0) {}

    void update(long long id, long long lo, long long hi, long long targetID, long long targetVal)
    {
        if (lo == hi) {
            data[id] = targetVal;
            return;
        }
        const long long mid = lo + (hi - lo) / 2;
        if (targetID <= mid) {
            update(2 * id, lo, mid, targetID, targetVal);
        } else {
            update(2 * id + 1, mid + 1, hi, targetID, targetVal);
        }
        data[id] = std::max(data[2 * id], data[2 * id + 1]);
    }

    // query range [1:R]
    long long query(long long id, long long lo, long long hi, long long R)
    {
        if (hi <= R)
            return data[id];

        const long long mid = lo + (hi - lo) / 2;
        if (R <= mid)
            return query(2 * id, lo, mid, R);

        return std::max(data[2 * id], query(2 * id + 1, mid + 1, hi, R));
    }

private:
    std::vector<long long> data;
};

class Solution
{
public:
    std::vector<bool> getResults(std::vector<std::vector<int>>& queries)
    {
        // consider 0 and MAX as two obstacles
        long long boundary = 0;
        for (const auto& query : queries) {
            boundary = std::max(boundary, static_cast<long long>(query[1]));
        }
        boundary++;
        const long long n = boundary + 1;
        SegmentTree tree(n);
        std::set<long long> obstacles{0, boundary};
        std::vector<bool> result;
        result.reserve(queries.size());
        for (const auto& query : queries) {
            // ... left_obstacle ... x ... right_obstacle
            //     |<-----x-left---->|<-----right-x---->|
            const long long x = query[1];
            auto iter = obstacles.lower_bound(x);
            const long long left = *std::prev(iter);
            const long long right = *iter;
            if (query[0] == 1) {
                obstacles.insert(x);
                tree.update(1, 1, n, x + 1, x - left);
                tree.update(1, 1, n, right + 1, right - x);
            } else {
                const int maxSpace = std::max(x - left, tree.query(1, 1, n, left + 1));
                result.push_back(maxSpace >= query[2]);
            }
        }
        return result;
    }
};