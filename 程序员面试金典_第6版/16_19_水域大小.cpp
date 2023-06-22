#include <algorithm>
#include <vector>

/**
 * 你有一个用于表示一片土地的整数矩阵land，该矩阵中每个点的值代表对应地点的海拔高度。
 *
 * 若值为0则表示水域。由垂直、水平或对角连接的水域为池塘。
 *
 * 池塘的大小是指相连接的水域的个数。
 *
 * 编写一个方法来计算矩阵中所有池塘的大小，返回值需要从小到大排序。
 *
 * ! 0 < len(land) <= 1000
 * ! 0 < len(land[i]) <= 1000
 */

class Solution
{
public:
    std::vector<int> pondSizes(std::vector<std::vector<int>>& land)
    {
        if (land.empty() || land[0].empty())
            return {};

        const auto m = land.size();
        const auto n = land[0].size();
        std::vector<int> result;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (land[i][j] == 0) {
                    result.push_back(dfs(i, j, land));
                }
            }
        }
        std::sort(result.begin(), result.end());
        return result;
    }

private:
    const std::vector<int> kOffsets{-1, 1, 0};
    int dfs(int x, int y, std::vector<std::vector<int>>& land)
    {
        const auto m = land.size();
        const auto n = land[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n)
            return 0;

        if (land[x][y] != 0)
            return 0;

        land[x][y] = -1;
        int count = 1;
        for (const auto& dx : kOffsets) {
            for (const auto& dy : kOffsets) {
                if (dx == 0 && dy == 0)
                    continue;

                count += dfs(x + dx, y + dy, land);
            }
        }
        return count;
    }
};