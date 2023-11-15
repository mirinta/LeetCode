#include <vector>

/**
 * You are given a 0-indexed integer array stations of length n, where stations[i] represents the
 * number of power stations in the ith city.
 *
 * Each power station can provide power to every city in a fixed range. In other words, if the range
 * is denoted by r, then a power station at city i can provide power to all cities j such that |i -
 * j| <= r and 0 <= i, j <= n - 1.
 *
 *
 * - Note that |x| denotes absolute value. For example, |7 - 5| = 2 and |3 - 10| = 7.
 *
 * The power of a city is the total number of power stations it is being provided power from.
 *
 * The government has sanctioned building k more power stations, each of which can be built in any
 * city, and have the same range as the pre-existing ones.
 *
 * Given the two integers r and k, return the maximum possible minimum power of a city, if the
 * additional power stations are built optimally.
 *
 * Note that you can build the k power stations in multiple cities.
 *
 * ! n == stations.length
 * ! 1 <= n <= 10^5
 * ! 0 <= stations[i] <= 10^5
 * ! 0 <= r <= n - 1
 * ! 0 <= k <= 10^9
 */

class Solution
{
public:
    long long maxPower(std::vector<int>& stations, int r, int k)
    {
        // guess the final answer: min power of each city
        long long lo = 0;
        long long hi = LLONG_MAX;
        while (lo < hi) {
            const auto mid = hi - (hi - lo) / 2;
            if (isValid(stations, r, k, mid)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }

private:
    bool isValid(std::vector<int> stations, int r, int k, long long minLimit)
    {
        // check if power[i] >= minLimit
        // if power[i] < min, use the k additional power stations to make power[i+r] = minLimit
        const int n = stations.size();
        // i-r-1 i-r X X X i X X X i+r
        //       |<------window----->|
        long long sum = 0;
        for (int i = 0; i < std::min(n, r); ++i) {
            sum += stations[i];
        }
        for (int i = 0; i < n; ++i) {
            if (i + r < n) {
                sum += stations[i + r];
            }
            if (i - r - 1 >= 0) {
                sum -= stations[i - r - 1];
            }
            if (sum >= minLimit)
                continue;

            const auto delta = minLimit - sum;
            if (delta > k)
                return false;

            stations[std::min(n - 1, i + r)] += delta;
            k -= delta;
            sum = minLimit;
        }
        return true;
    }
};