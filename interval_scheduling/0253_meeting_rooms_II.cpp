#include <algorithm>
#include <vector>

/**
 * Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return
 * the minimum number of conference rooms required.
 *
 * ! 1 <= intervals.length <= 10^4
 * ! 0 <= starti < endi <= 10^6
 */

class Solution
{
public:
    int minMeetingRooms(std::vector<std::vector<int>>& intervals)
    {
        const int n = intervals.size();
        std::vector<int> startPoints(n, 0);
        std::vector<int> endPoints(n, 0);
        for (int i = 0; i < n; ++i) {
            startPoints[i] = intervals[i][0];
            endPoints[i] = intervals[i][1];
        }
        std::sort(startPoints.begin(), startPoints.end());
        std::sort(endPoints.begin(), endPoints.end());
        int count = 0;
        int result = 0;
        int i = 0; // loop start points
        int j = 0; // loop end points
        while (i < n && j < n) {
            if (startPoints[i] < endPoints[j]) {
                i++;
                count++;
            } else {
                j++;
                count--;
            }
            result = std::max(result, count);
        }
        return result;
    }
};