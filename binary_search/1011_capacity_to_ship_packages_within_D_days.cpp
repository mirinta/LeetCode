#include <algorithm>
#include <numeric>
#include <vector>

/**
 * A conveyor belt has packages that must be shipped from one port to another within "days" days.
 *
 * The "i"th package on teh conveyor belt has a weight of "weights[i]". Each day, we load the ship
 * with packages on the conveyor (in the order given by "weights"). We may not load more weight than
 * the maximum weight capacity of the ship.
 *
 * Return the least weight capacity of the ship that will result in all packages on teh conveyor
 * belt being shipped within "days" days.
 *
 * ! Note that the cargo must be shipped in the order given.
 *
 * ! 1 <= days <= weights.length <= 5 * 10^4
 * ! 1 <= weights[i] <= 500
 */

class Solution
{
public:
    int shipWithinDays(std::vector<int>& weights, int days)
    {
        // guess the final answer
        int lo = *std::max_element(weights.begin(), weights.end());
        int hi = std::accumulate(weights.begin(), weights.end(), 0);
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, weights, days)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    bool isValid(int capacity, const std::vector<int>& weights, int days)
    {
        int time = 1;
        int sum = 0;
        for (const auto& w : weights) {
            if (w > capacity)
                return false;

            sum += w;
            if (sum > capacity) {
                time++;
                sum = w;
            }
            if (time > days)
                return false;
        }
        return true;
    }
};