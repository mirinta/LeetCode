#include <algorithm>
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
        return approach2(stations, r, k);
    }

private:
    // binary search + sliding window, TC = O(NlogK), SC = O(N)
    long long approach2(const std::vector<int>& stations, int r, int k)
    {
        auto isValid = [](long long min, int r, int k, std::vector<int> stations) {
            // ... i-r i-r+1 ... i i+1 ... i+r i+r+1...
            //     |<----------------------->|
            //         |<------------------------->|
            // power[i] = sum of stations[i-r:i+r]
            const int n = stations.size();
            long long power = 0;
            for (int i = 0; i < std::min(n, r); ++i) {
                power += stations[i];
            }
            for (int i = 0; i < n; ++i) {
                if (i + r < n) {
                    power += stations[i + r];
                }
                if (i - r - 1 >= 0) {
                    power -= stations[i - r - 1];
                }
                if (power >= min)
                    continue;

                const long long extra = min - power;
                if (extra > k)
                    return false;

                power += extra;
                stations[std::min(n - 1, i + r)] += extra;
                k -= extra;
            }
            return true;
        };
        long long lo = 0;
        long long hi = LLONG_MAX;
        while (lo < hi) {
            const long long mid = hi - (hi - lo) / 2;
            if (isValid(mid, r, k, stations)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }

    // binary search + prefix sum + difference array, TC = O(NlogK), SC = O(N)
    long long approach1(const std::vector<int>& stations, int r, int k)
    {
        const int n = stations.size();
        std::vector<long long> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + stations[i - 1];
        }
        std::vector<long long> power(n, 0);
        for (int i = 0; i < n; ++i) {
            // power[i] = sum of stations[i-r:i+r]
            power[i] = presum[std::min(n - 1, i + r) + 1] - presum[std::max(0, i - r)];
        }
        std::vector<long long> diff(n, 0); // diff[i] = power[i] - power[i-1]
        diff[0] = power[0];
        for (int i = 1; i < n; ++i) {
            diff[i] = power[i] - power[i - 1];
        }
        // check the min power of a city >= min, after building k more stations
        auto isValid = [](long long min, int r, int k, std::vector<long long> diff) {
            const int n = diff.size();
            for (int i = 0; i < n; ++i) {
                diff[i] += i > 0 ? diff[i - 1] : 0; // diff[i] = power[i]
                if (diff[i] >= min)
                    continue;

                const long long extra = min - diff[i];
                if (extra > k)
                    return false;

                // build extra stations at city j
                // we don't want city j covers city[0:i-1],
                // because power[0:i-1] are already >= min
                const int j = std::min(n - 1, i + r);
                diff[i] += extra;
                const int hi = std::min(n - 1, j + r);
                if (hi + 1 < n) {
                    diff[hi + 1] -= extra;
                }
                k -= extra;
            }
            return true;
        };
        // guess the final answer
        long long lo = *std::min_element(power.begin(), power.end());
        long long hi = lo + k;
        while (lo < hi) {
            const long long mid = hi - (hi - lo) / 2;
            if (isValid(mid, r, k, diff)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }
};