#include <string>
#include <vector>

/**
 * Along a long library corridor, there is a line of seats and decorative plants. You are given a
 * 0-indexed string corridor of length n consisting of letters 'S' and 'P' where each 'S' represents
 * a seat and each 'P' represents a plant.
 *
 * One room divider has already been installed to the left of index 0, and another to the right of
 * index n - 1. Additional room dividers can be installed. For each position between indices i - 1
 * and i (1 <= i <= n - 1), at most one divider can be installed.
 *
 * Divide the corridor into non-overlapping sections, where each section has exactly two seats with
 * any number of plants. There may be multiple ways to perform the division. Two ways are different
 * if there is a position with a room divider installed in the first way but not in the second way.
 *
 * Return the number of ways to divide the corridor. Since the answer may be very large, return it
 * modulo 10^9 + 7. If there is no way, return 0.
 *
 * ! n == corridor.length
 * ! 1 <= n <= 10^5
 * ! corridor[i] is either 'S' or 'P'.
 */

class Solution
{
public:
    int numberOfWays(std::string corridor)
    {
        constexpr int kMod = 1e9 + 7;
        const int n = corridor.size();
        std::vector<int> seats;
        for (int i = 0; i < n; ++i) {
            if (corridor[i] == 'S') {
                seats.push_back(i);
            }
        }
        if (seats.size() < 2 || seats.size() % 2 != 0)
            return 0;

        // 0 1 | 4 6
        //   |<->| diff
        long long result = 1;
        for (int i = 2; i + 2 <= seats.size(); i += 2) {
            const int diff = seats[i] - seats[i - 1];
            result = result * diff % kMod;
        }
        return result;
    }
};