#include <vector>

/**
 * There are n flights that are labeled from 1 to n.
 *
 * You are given an array of flight bookings bookings, where bookings[i] = [firsti, lasti, seatsi]
 * represents a booking for flights firsti through lasti (inclusive) with seatsi seats reserved for
 * each flight in the range.
 *
 * Return an array answer of length n, where answer[i] is the total number of seats reserved for
 * flight i.
 *
 * ! 1 <= n <= 2 * 10^4
 * ! 1 <= bookings.length <= 2 * 10^4
 * ! bookings[i].length == 3
 * ! 1 <= firsti <= lasti <= n
 * ! 1 <= seatsi <= 10^4
 */

class Solution
{
public:
    std::vector<int> corpFlightBookings(std::vector<std::vector<int>>& bookings, int n)
    {
        // let diff[i] = seats[i]-seats[i-1]
        // when we add add value x to seats[i:j],
        // we need seats[j+1] -= x and seats[i] += x
        std::vector<int> diff(n, 0); // diff[i] = seats[i]-seats[i-1]
        for (const auto& booking : bookings) {
            diff[booking[0] - 1] += booking[2];
            if (booking[1] < n) {
                diff[booking[1]] -= booking[2];
            }
        }
        for (int i = 1; i < n; ++i) {
            diff[i] += diff[i - 1];
        }
        return diff;
    }
};