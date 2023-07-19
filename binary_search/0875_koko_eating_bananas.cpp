#include <algorithm>
#include <cmath>
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
    int minEatingSpeed(std::vector<int>& piles, int h)
    {
        int lo = 1;
        int hi = *std::max_element(piles.begin(), piles.end());
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, h, piles)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    bool isValid(int speed, int timeLimit, const std::vector<int>& piles)
    {
        int time = 0;
        for (const auto& pile : piles) {
            if (speed >= pile) {
                time++;
            } else {
                time += std::ceil(pile * 1.0 / speed);
            }
            if (time > timeLimit)
                return false;
        }
        return true;
    }
};