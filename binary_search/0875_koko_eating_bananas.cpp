#include <vector>

/**
 * Koko loves to eat bananas. There are "n" piles of bananas, the "i"th pile has "piles[i]" bananas.
 * The guards have gone and will come back in "h" hours.
 *
 * Koko can decide her bananas-per-hour eating speed of "k". Each hour, she chooses some pile of
 * bananas and eats "k" bananas from that pile. If the pile has less than "k" bananas, she eats all
 * of them instead and will not eat any more bananas during this hour.
 *
 * Koko likes to eat slowly but still wants to finish eating all the bananas before the guards
 * return.
 *
 * Return the minimum integer "k" such that she can eat all the bananas within "h" hours.
 */

class Solution
{
public:
    int minEatingSpeed(const std::vector<int>& piles, int h)
    {
        if (piles.empty() || h <= 0 || h < piles.size())
            return -1;

        // search range [1, maxBananasOfPile]
        int maxBananas = INT_MIN;
        for (const auto& bananas : piles) {
            maxBananas = bananas > maxBananas ? bananas : maxBananas;
        }
        int left = 1;
        int right = maxBananas;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (isSatisfied(piles, h, mid)) {
                right = mid - 1; // decrease upper bound
            } else {
                left = mid + 1;
            }
        } // the loop is terminated when left = right + 1 = mid
        return right + 1;
    }

private:
    bool isSatisfied(const std::vector<int>& piles, int h, int speed)
    {
        int count = 0;
        for (const auto& bananas : piles) {
            int hours = bananas / speed;
            count += bananas % speed == 0 ? hours : hours + 1;
            if (count > h)
                return false;
        }
        return true;
    }
};