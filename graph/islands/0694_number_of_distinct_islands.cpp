#include <unordered_set>
#include <vector>

/**
 * You are given an m x n binary matrix grid. An island is a group of 1's (representing land)
 * connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are
 * surrounded by water.
 *
 * An island is considered to be the same as another if and only if one island can be translated
 * (and not rotated or reflected) to equal the other.
 *
 * Return the number of distinct islands.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 50
 * ! grid[i][j] is either 0 or 1.
 */

class Solution
{
public:
    int numDistinctIslands(std::vector<std::vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int m = grid.size();
        const int n = grid[0].size();
        std::unordered_set<std::string> set;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != kLand)
                    continue;

                std::string encode;
                dfs(encode, i, j, grid);
                set.insert(std::move(encode));
            }
        }
        return set.size();
    }

private:
    static constexpr int kLand = 1;
    static constexpr int kWater = 0;
    static constexpr char kUp = 'U';
    static constexpr char kDown = 'D';
    static constexpr char kLeft = 'L';
    static constexpr char kRight = 'R';
    static constexpr char kEnd = '0';

    void dfs(std::string& encode, int x, int y, std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != kLand) {
            if (!encode.empty()) {
                encode.pop_back();
            }
            return;
        }
        grid[x][y] = kWater;
        // go up:
        encode.push_back(kUp);
        dfs(encode, x - 1, y, grid);
        // go down:
        encode.push_back(kDown);
        dfs(encode, x + 1, y, grid);
        // go left:
        encode.push_back(kLeft);
        dfs(encode, x, y - 1, grid);
        // go right:
        encode.push_back(kRight);
        dfs(encode, x, y + 1, grid);
        // end of search:
        encode.push_back(kEnd);
    }
};