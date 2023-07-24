#include <algorithm>
#include <vector>

/**
 * There are some spherical balloons taped onto a flat wall that represents the XY-plane. The
 * balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a
 * balloon whose horizontal diameter stretches between xstart and xend. You do not know the exact
 * y-coordinates of the balloons.
 *
 * Arrows can be shot up directly vertically (in the positive y-direction) from different points
 * along the x-axis. A balloon with xstart and xend is burst by an arrow shot at x if xstart <= x <=
 * xend. There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up
 * infinitely, bursting any balloons in its path.
 *
 * Given the array points, return the minimum number of arrows that must be shot to burst all
 * balloons.
 *
 * ! 1 <= points.length <= 10^5
 * ! points[i].length == 2
 * ! -2^31 <= xstart < xend <= 2^31 - 1
 */

class Solution
{
public:
    int findMinArrowShots(std::vector<std::vector<int>>& points)
    {
        // min arrows = max num of non-overlapping intervals
        const int n = points.size();
        std::sort(points.begin(), points.end(),
                  [](const auto& v1, const auto& v2) { return v1[1] < v2[1]; });
        int count = 1; // one arrow for bursting the first balloon
        int endingPoint = points[0][1];
        for (int i = 1; i < n; ++i) {
            if (points[i][0] > endingPoint) {
                endingPoint = points[i][1];
                count++;
            }
        }
        return count;
    }
};