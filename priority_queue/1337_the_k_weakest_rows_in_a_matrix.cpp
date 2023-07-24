#include <queue>
#include <vector>

/**
 * You are given an m x n binary matrix mat of 1's (representing soldiers) and 0's (representing
 * civilians). The soldiers are positioned in front of the civilians. That is, all the 1's will
 * appear to the left of all the 0's in each row.
 *
 * A row i is weaker than a row j if one of the following is true:
 *
 * - The number of soldiers in row i is less than the number of soldiers in row j.
 *
 * - Both rows have the same number of soldiers and i < j.
 *
 * Return the indices of the k weakest rows in the matrix ordered from weakest to strongest.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 2 <= n, m <= 100
 * ! 1 <= k <= m
 * ! matrix[i][j] is either 0 or 1.
 */

class Solution
{
public:
    std::vector<int> kWeakestRows(std::vector<std::vector<int>>& mat, int k)
    {
        // priority queue + binary search
        std::priority_queue<std::pair<int, int>> pq; // max heap
        for (int i = 0; i < mat.size(); ++i) {
            auto iter = std::upper_bound(mat[i].rbegin(), mat[i].rend(), 0);
            const int soldiers = std::distance(iter, mat[i].rend());
            pq.push({soldiers, i});
            if (pq.size() > k) {
                pq.pop();
            }
        }
        std::vector<int> result(std::min<size_t>(k, pq.size()));
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] = pq.top().second;
            pq.pop();
        }
        return result;
    }
};