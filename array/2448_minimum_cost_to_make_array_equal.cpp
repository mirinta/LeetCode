#include <algorithm>
#include <vector>

/**
 * You are given two 0-indexed arrays nums and cost consisting each of n positive integers.
 *
 * You can do the following operation any number of times:
 *
 * - Increase or decrease any element of the array nums by 1.
 *
 * The cost of doing one operation on the ith element is cost[i].
 *
 * Return the minimum total cost such that all the elements of the array nums become equal.
 *
 * ! n == nums.length == cost.length
 * ! 1 <= n <= 10^5
 * ! 1 <= nums[i], cost[i] <= 10^6
 *
 * Example:
 * Input: nums = [1,3,5,2], cost = [2,3,1,14]
 * Output: 8
 * Explanation: We can make all the elements equal to 2 in the following way:
 * - Increase the 0th element one time. The cost is 2.
 * - Decrease the 1st element one time. The cost is 3.
 * - Decrease the 2nd element three times. The cost is 1 + 1 + 1 = 3.
 * The total cost is 2 + 3 + 3 = 8.
 * It can be shown that we cannot make the array equal with a smaller cost.
 */

class Solution
{
public:
    long long minCost(std::vector<int>& nums, std::vector<int>& cost)
    {
        const int n = nums.size();
        std::vector<std::pair<long long, long long>> pairs(n);
        for (int i = 0; i < n; ++i) {
            pairs[i].first = nums[i];
            pairs[i].second = cost[i];
        }
        std::sort(pairs.begin(), pairs.end());
        // After sorting, total cost of making elements equal to nums[i] = LEFT + RIGHT
        // - LEFT  = cost of increasing nums[0:i-1] to nums[i]
        // - RIGHT = cost of decreasing nums[n-1:i+1] to nums[i]
        std::vector<long long> left(n, 0);
        long long prefixCost = pairs.front().second;
        for (int i = 1; i < n; ++i) {
            left[i] = left[i - 1] + (pairs[i].first - pairs[i - 1].first) * prefixCost;
            prefixCost += pairs[i].second;
        }
        std::vector<long long> right(n, 0);
        long long suffixCost = pairs.back().second;
        for (int i = n - 2; i >= 0; --i) {
            right[i] = right[i + 1] + (pairs[i + 1].first - pairs[i].first) * suffixCost;
            suffixCost += pairs[i].second;
        }
        long long result = LLONG_MAX;
        for (int i = 0; i < n; ++i) {
            result = std::min(result, left[i] + right[i]);
        }
        return result;
    }
};

// the optimal value is one of the element in nums
// say we have two numbers p and q, where p < q
// and the costs doing one operation on p, q are cost_p, cost_q
// - consider p < x-1 < x < x+1 < q
// - cost of making p and q equal to x   = cost0 = (x-p)cost_p + (x-q)cost_q
// - cost of making p and q equal to x+1 = cost1 = (x-p+1)cost_p + (x-q-1)cost_q
// - cost of making p and q equal to x-1 = cost2 = (x-p-1)cost_p + (x-q+1)cost_q
// - cost1 - cost0 = cost_p - cost_q
// - cost2 - cost0 = cost_q - cost_p
// if cost_p > cost_q, then cost2 < cost0, which means x-1 is better than x
// keep decreasing x until it becomes p, and p is the optimal value