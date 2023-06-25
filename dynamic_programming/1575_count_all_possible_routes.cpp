#include <vector>

/**
 * You are given an array of distinct positive integers locations where locations[i] represents the
 * position of city i. You are also given integers start, finish and fuel representing the starting
 * city, ending city, and the initial amount of fuel you have, respectively.
 *
 * At each step, if you are at city i, you can pick any city j such that j != i and 0 <= j <
 * locations.length and move to city j. Moving from city i to city j reduces the amount of fuel you
 * have by |locations[i] - locations[j]|. Please notice that |x| denotes the absolute value of x.
 *
 * Notice that fuel cannot become negative at any point in time, and that you are allowed to visit
 * any city more than once (including start and finish).
 *
 * Return the count of all possible routes from start to finish. Since the answer may be too large,
 * return it modulo 10^9 + 7.
 *
 * ! 2 <= locations.length <= 100
 * ! 1 <= locations[i] <= 10^9
 * ! All integers in locations are distinct.
 * ! 0 <= start, finish < locations.length
 * ! 1 <= fuel <= 200
 */

class Solution
{
public:
    int countRoutes(std::vector<int>& locations, int start, int finish, int fuel)
    {
        constexpr int kMod = 1e9 + 7;
        // dp[f][c] = num of routes when arriving at city c with f remaining fuel
        int dp[201][101] = {0};
        dp[fuel][start] = 1;
        const int n = locations.size();
        for (int f = fuel; f >= 0; --f) {
            for (int c = 0; c < n; ++c) {
                for (int k = 0; k < n; ++k) {
                    if (k == c)
                        continue;
                    // amount of consuming fuel from city k to city c
                    const int cost = std::abs(locations[c] - locations[k]);
                    if (f + cost <= fuel) {
                        dp[f][c] = (dp[f][c] + dp[f + cost][k]) % kMod;
                    }
                }
            }
        }
        int result = 0;
        for (int f = fuel; f >= 0; --f) {
            result = (result + dp[f][finish]) % kMod;
        }
        return result;
    }
};