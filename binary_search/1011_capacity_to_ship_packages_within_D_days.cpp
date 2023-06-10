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
 */

class Solution
{
public:
    int shipWithinDays(const std::vector<int>& weights, int days)
    {
        if (weights.empty() || days <= 0)
            return -1;

        // the capacity >= the max value of weights
        int maxWeight = INT_MIN;
        int totalWeights = 0;
        for (const auto& w : weights) {
            totalWeights += w;
            maxWeight = w > maxWeight ? w : maxWeight;
        }
        // search range [maxWeight, totalWeights]
        int left = maxWeight;
        int right = totalWeights;
        int capacity = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (isSatisfied(weights, days, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } // the loop is terminated when left = right + 1 = mid
        return right + 1;
    }

private:
    bool isSatisfied(const std::vector<int>& weights, int days, int capacity)
    {
        int count = 1;
        int carried = 0;
        for (const auto& weight : weights) {
            if (weight > capacity)
                return false;

            if (carried + weight > capacity) {
                if (++count > days)
                    return false;

                carried = weight;
            } else {
                carried += weight;
            }
        }
        return true;
    }
};