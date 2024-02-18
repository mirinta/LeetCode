#include <queue>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer n. There are n rooms numbered from 0 to n - 1.
 *
 * You are given a 2D integer array meetings where meetings[i] = [starti, endi] means that a meeting
 * will be held during the half-closed time interval [starti, endi). All the values of starti are
 * unique.
 *
 * Meetings are allocated to rooms in the following manner:
 *
 * Each meeting will take place in the unused room with the lowest number.
 * If there are no available rooms, the meeting will be delayed until a room becomes free. The
 * delayed meeting should have the same duration as the original meeting. When a room becomes
 * unused, meetings that have an earlier original start time should be given the room. Return the
 * number of the room that held the most meetings. If there are multiple rooms, return the room with
 * the lowest number.
 *
 * A half-closed interval [a, b) is the interval between a and b including a and not including b.
 *
 * ! 1 <= n <= 100
 * ! 1 <= meetings.length <= 10^5
 * ! meetings[i].length == 2
 * ! 0 <= starti < endi <= 5 * 10^5
 * ! All the values of starti are unique.
 */

class Solution
{
public:
    int mostBooked(int n, std::vector<std::vector<int>>& meetings)
    {
        std::sort(meetings.begin(), meetings.end());
        using Pair = std::pair<long long, int>; // <available time, room id>
        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> occupiedRooms;
        std::priority_queue<int, std::vector<int>, std::greater<>> availableRooms;
        for (int i = 0; i < n; ++i) {
            availableRooms.push(i);
        }
        std::vector<int> count(n, 0);
        for (const auto& meeting : meetings) {
            const int start = meeting[0];
            const int end = meeting[1];
            while (!occupiedRooms.empty() && occupiedRooms.top().first <= start) {
                availableRooms.push(occupiedRooms.top().second);
                occupiedRooms.pop();
            }
            if (!availableRooms.empty()) {
                const int room = availableRooms.top();
                availableRooms.pop();
                count[room]++;
                occupiedRooms.emplace(end, room);
            } else {
                const auto [availableTime, room] = occupiedRooms.top();
                occupiedRooms.pop();
                count[room]++;
                occupiedRooms.emplace(availableTime + end - start, room);
            }
        }
        return std::max_element(count.begin(), count.end()) - count.begin();
    }
};