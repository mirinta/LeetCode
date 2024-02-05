#include <vector>

/**
 * You are given a 2D array points of size n x 2 representing integer coordinates of some points on
 * a 2D-plane, where points[i] = [xi, yi].
 *
 * We define the right direction as positive x-axis (increasing x-coordinate) and the left direction
 * as negative x-axis (decreasing x-coordinate). Similarly, we define the up direction as positive
 * y-axis (increasing y-coordinate) and the down direction as negative y-axis (decreasing
 * y-coordinate)
 *
 * You have to place n people, including Chisato and Takina, at these points such that there is
 * exactly one person at every point. Chisato wants to be alone with Takina, so Chisato will build a
 * rectangular fence with Chisato's position as the upper left corner and Takina's position as the
 * lower right corner of the fence (Note that the fence might not enclose any area, i.e. it can be a
 * line). If any person other than Chisato and Takina is either inside the fence or on the fence,
 * Chisato will be sad.
 *
 * Return the number of pairs of points where you can place Chisato and Takina, such that Chisato
 * does not become sad on building the fence.
 *
 * Note that Chisato can only build a fence with Chisato's position as the upper left corner, and
 * Takina's position as the lower right corner. For example, Chisato cannot build either of the
 * fences in the picture below with four corners (1, 1), (1, 3), (3, 1), and (3, 3), because:
 *
 * - With Chisato at (3, 3) and Takina at (1, 1), Chisato's position is not the upper left corner
 * and Takina's position is not the lower right corner of the fence.
 *
 * - With Chisato at (1, 3) and Takina at (1, 1), Takina's position is not the lower right corner of
 * the fence.
 *
 * ! 2 <= n <= 50
 * ! points[i].length == 2
 * ! 0 <= points[i][0], points[i][1] <= 50
 * ! All points[i] are distinct.
 */

class Solution
{
public:
    int numberOfPairs(std::vector<std::vector<int>>& points)
    {
        const int n = points.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isValid(i, j, points)) {
                    result++;
                }
            }
        }
        return result;
    }

private:
    bool isValid(int i, int j, const std::vector<std::vector<int>>& points)
    {
        const int x1 = points[i][0];
        const int y1 = points[i][1];
        const int x2 = points[j][0];
        const int y2 = points[j][1];
        // case 1: (x1, y1) is the top-left corner, then x2 > x1 and y2 < y1
        // case 2: (x2, y2) is the top-left corner, then x1 > x2 and y1 < y2
        const bool case1 = x2 >= x1 && y2 <= y1;
        const bool case2 = x1 >= x2 && y1 <= y2;
        if (!case1 && !case2)
            return false;

        for (int k = 0; k < points.size(); ++k) {
            if (k == i || k == j)
                continue;

            const int x = points[k][0];
            const int y = points[k][1];
            if (x >= std::min(x1, x2) && x <= std::max(x1, x2) && y >= std::min(y1, y2) &&
                y <= std::max(y1, y2))
                return false;
        }
        return true;
    }
};