#include <algorithm>
#include <cmath>
#include <vector>

/**
 * You are given two positive integer arrays spells and potions, of length n and m respectively,
 * where spells[i] represents the strength of the ith spell and potions[j] represents the strength
 * of the jth potion.
 *
 * You are also given an integer success. A spell and potion pair is considered successful if the
 * product of their strengths is at least success.
 *
 * Return an integer array pairs of length n where pairs[i] is the number of potions that will form
 * a successful pair with the ith spell.
 *
 * ! n == spells.length
 * ! m == potions.length
 * ! 1 <= n, m <= 10^5
 * ! 1 <= spells[i], potions[i] <= 10^5
 * ! 1 <= success <= 10^10
 */

class Solution
{
public:
    std::vector<int> successfulPairs(std::vector<int>& spells, std::vector<int>& potions,
                                     long long success)
    {
        std::sort(potions.begin(), potions.end());
        const int n = spells.size();
        std::vector<int> result(n, 0);
        for (int i = 0; i < n; ++i) {
            // find the first element >= target
            // - ceil(a/b) = a/b if a%b=0 else a/b+1
            // using STL:
            // const auto target = std::ceil(success * 1.0 / spells[i]);
            // auto iter = std::lower_bound(potions.begin(), potions.end(), target);
            // if (iter != potions.end()) {
            //     result[i] = std::distance(iter, potions.end());
            // }
            const int index =
                findFirstGreaterOrEqualTo(std::ceil(success * 1.0 / spells[i]), potions);
            if (index != -1) {
                result[i] = potions.size() - index;
            }
        }
        return result;
    }

private:
    // input array is sorted in ascending order
    int findFirstGreaterOrEqualTo(long long target, const std::vector<int>& nums)
    {
        if (nums.empty())
            return -1;

        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] >= target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo == nums.size() ? -1 : lo;
    }
};