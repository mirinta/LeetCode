#include <algorithm>
#include <numeric>
#include <vector>

/**
 * You are given an array of positive integers nums of length n.
 *
 * A polygon is a closed plane figure that has at least 3 sides. The longest side of a polygon is
 * smaller than the sum of its other sides.
 *
 * Conversely, if you have k (k >= 3) positive real numbers a1, a2, a3, ..., ak where a1 <= a2 <= a3
 * <= ... <= ak and a1 + a2 + a3 + ... + ak-1 > ak, then there always exists a polygon with k sides
 * whose lengths are a1, a2, a3, ..., ak.
 *
 * The perimeter of a polygon is the sum of lengths of its sides.
 *
 * Return the largest possible perimeter of a polygon whose sides can be formed from nums, or -1 if
 * it is not possible to create a polygon.
 *
 * ! 3 <= n <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution
{
public:
    long long largestPerimeter(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        // search i from right to left,
        // if nums[0:i] is a valid polygon then it is the polygon which has the largest perimeter
        // - condition 1: i >= 2
        // - condition 2: sum[0:i-1] > nums[i] => sum[0:i] - nums[i] > nums[i]
        long long sum = std::accumulate(nums.begin(), nums.end(), 0LL);
        for (int i = n - 1; i >= 2; --i) {
            if (sum - nums[i] > nums[i])
                return sum;

            sum -= nums[i];
        }
        return -1;
    }
};