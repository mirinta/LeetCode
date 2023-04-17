#include <vector>

/**
 * There are "n" flights that are labeled from "1" to "n".
 *
 * You are given an array of flight bookings "bookings", where "bookings[i] = [first_i, last_i,
 * seats_i]" represents a booking for flights "first_i" through "last_i" (inclusive) with "seats_i"
 * seats reserved for each flight in the range.
 *
 * Return an array "answer" of length "n", where "answer[i]" is the total number of seats reserved
 * for flight i.
 */

class Solution
{
public:
    std::vector<int> corpFlightBookings(std::vector<std::vector<int>>& bookings, int n)
    {
        // let diffs = [d0, d1, ..., d(n-1)]
        // where di = fi - f(i-1), fi is the total number of seats reserved for flight i
        // - if add "val" to [fi, fj], then diffs[i] += val and diffs[j+1] -= val (if j+1 < n)
        // - to get the output, let diffs[i] += diffs[i - 1]
        if (n <= 0)
            return {};

        std::vector<int> diffs(n, 0);
        for (const auto& booking : bookings) {
            diffs[booking[0] - 1] += booking[2]; // booking[0] and booking[1] are 1-indexed
            if (booking[1] < diffs.size()) {
                diffs[booking[1]] -= booking[2];
            }
        }
        for (size_t i = 1; i < diffs.size(); ++i) {
            diffs[i] += diffs[i - 1];
        }
        return diffs;
    }
};