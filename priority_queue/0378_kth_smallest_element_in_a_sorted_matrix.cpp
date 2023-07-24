#include <queue>
#include <vector>

/**
 * Given an n x n matrix where each of the rows and columns is sorted in ascending order, return the
 * kth smallest element in the matrix.
 *
 * Note that it is the kth smallest element in the sorted order, not the kth distinct element.
 *
 * You must find a solution with a memory complexity better than O(n2).
 *
 * ! n == matrix.length == matrix[i].length
 * ! 1 <= n <= 300
 * ! -10^9 <= matrix[i][j] <= 10^9
 * ! All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order.
 * ! 1 <= k <= n^2
 */

class Solution
{
public:
    int kthSmallest(std::vector<std::vector<int>>& matrix, int k) { return approach2(matrix, k); }

private:
    int approach2(std::vector<std::vector<int>>& matrix, int k)
    {
        auto comp = [](const auto& t1, const auto& t2) -> bool {
            return std::get<0>(t1) > std::get<0>(t2);
        };
        // min heap
        using Tuples = std::vector<std::tuple<int, int, int>>;
        std::priority_queue<std::tuple<int, int, int>, Tuples, decltype(comp)> pq(comp);
        for (int i = 0; i < matrix.size(); ++i) {
            pq.push({matrix[i][0], i, 0});
        }
        int result = -1;
        while (!pq.empty() && k > 0) {
            k--;
            const auto [val, i, j] = pq.top();
            pq.pop();
            result = val;
            if (j + 1 < matrix[i].size()) {
                pq.push({matrix[i][j + 1], i, j + 1});
            }
        }
        return result;
    }

    int approach1(std::vector<std::vector<int>>& matrix, int k)
    {
        std::priority_queue<int> pq; // max heap
        for (const auto& rows : matrix) {
            for (const auto& val : rows) {
                pq.push(val);
                if (pq.size() > k) {
                    pq.pop();
                }
            }
        }
        return pq.top();
    }
};