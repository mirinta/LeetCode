#include <utility>

/**
 * You are given three positive integers: n, index, and maxSum. You want to construct an array nums
 * (0-indexed) that satisfies the following conditions:
 *
 * - nums.length == n.
 *
 * - nums[i] is a positive integer where 0 <= i < n.
 *
 * - abs(nums[i], nums[i + 1]) <= 1 where 0 <= i < n - 1.
 *
 * - The sum of all the elements of nums does not exceed maxSum.
 *
 * - nums[index] is maximized.
 *
 * Return nums[index] of the constructed array.
 *
 * Note that abs(x) equals x if x >= 0, and -x otherwise.
 *
 * ! 1 <= n <= maxSum <= 10^9
 * ! 0 <= index < n
 */

class Solution
{
public:
    int maxValue(int n, int index, int maxSum)
    {
        int lo = 1;
        int hi = maxSum;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (sum(mid, index, n) <= static_cast<long>(maxSum)) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } // the loop is terminated when lo = hi + 1
        return lo - 1;
    }

private:
    long sum(long val, long index, long n)
    {
        // {1,...,1,1,2,...,val-1}  val  {val-1,...,2,1,1,...,1}
        // {0,...,index-2,index-1} index {index+1,index+2,...,n-1}
        long leftItems = std::max(std::min(index, val - 1), 0L);
        long leftRemaining = std::max(0L, index - leftItems);
        long leftSum = (val - 1 + val - leftItems) * leftItems / 2 + leftRemaining;

        long rightItems = std::max(std::min(n - 1 - index, val - 1), 0L);
        long rightRemaining = std::max(0L, n - 1 - index - rightItems);
        long rightSum = (val - 1 + val - rightItems) * rightItems / 2 + rightRemaining;

        return leftSum + rightSum + val;
    }
};