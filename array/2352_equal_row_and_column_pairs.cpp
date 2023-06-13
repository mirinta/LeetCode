#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given a 0-indexed n x integer matrix "grid", return the number of pairs (r_i, c_i) such that row
 * r_i and column c_i are equal.
 *
 * A row and column pair is considered equal if they contain the same elements in the same order
 * (i.e., an equal array).
 *
 * ! n == grid.length == grid[i].length
 * ! 1 <= n <= 200
 * ! 1 <= grid[i][j] <= 10^5
 */

class Solution
{
public:
    int equalPairs(const std::vector<std::vector<int>>& grid)
    {
        const auto n = grid.size();
        std::unordered_map<std::string, int> map;
        for (size_t row = 0; row < n; ++row) {
            std::string rowString{};
            for (const auto& val : grid[row]) {
                rowString.append(std::to_string(val));
                rowString.push_back(',');
            }
            map[rowString]++;
        }
        int result = 0;
        for (size_t col = 0; col < n; ++col) {
            std::string colString{};
            for (size_t row = 0; row < n; ++row) {
                colString.append(std::to_string(grid[row][col]));
                colString.push_back(',');
            }
            if (map.count(colString)) {
                result += map[colString];
            }
        }
        return result;
    }
};