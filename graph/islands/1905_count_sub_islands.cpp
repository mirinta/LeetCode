#include <vector>

/**
 * You are given two m x n binary matrices grid1 and grid2 containing only 0's (representing water)
 * and 1's (representing land). An island is a group of 1's connected 4-directionally (horizontal or
 * vertical). Any cells outside of the grid are considered water cells.
 *
 * An island in grid2 is considered a sub-island if there is an island in grid1 that contains all
 * the cells that make up this island in grid2.
 *
 * Return the number of islands in grid2 that are considered sub-islands.
 *
 * ! m == grid1.length == grid2.length
 * ! n == grid1[i].length == grid2[i].length
 * ! 1 <= m, n <= 500
 * ! grid1[i][j] and grid2[i][j] are either 0 or 1.
 */

class Solution
{
public:
    int countSubIslands(std::vector<std::vector<int>>& grid1, std::vector<std::vector<int>>& grid2)
    {
        if (grid1.empty() || grid1[0].empty())
            return 0;

        if (grid1.size() != grid2.size() || grid1[0].size() != grid2[0].size())
            return 0;

        const int m = grid1.size();
        const int n = grid1[0].size();
        // if grid2(i,j)=1, but grid1(i,j)!=1
        // all lands in grid2 connected with grid2(i,j) are not sub-islands
        // thus, flood them with water
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid2[i][j] == kLand && grid1[i][j] != kLand) {
                    dfs(i, j, grid2);
                }
            }
        }
        // now, all lands in grid2 are sub-islands
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid2[i][j] == kLand) {
                    result++;
                    dfs(i, j, grid2);
                }
            }
        }
        return result;
    }

private:
    static constexpr int kLand = 1;
    static constexpr int kWater = 0;

    void dfs(int x, int y, std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != kLand)
            return;

        grid[x][y] = kWater;
        dfs(x + 1, y, grid);
        dfs(x - 1, y, grid);
        dfs(x, y + 1, grid);
        dfs(x, y - 1, grid);
    }
};