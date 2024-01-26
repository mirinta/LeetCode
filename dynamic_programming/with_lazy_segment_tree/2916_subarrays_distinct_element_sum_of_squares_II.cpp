#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed integer array nums.
 *
 * The distinct count of a subarray of nums is defined as:
 *
 * - Let nums[i..j] be a subarray of nums consisting of all the indices from i to j such that 0 <= i
 * <= j < nums.length. Then the number of distinct values in nums[i..j] is called the distinct count
 * of nums[i..j]. Return the sum of the squares of distinct counts of all subarrays of nums.
 *
 * Since the answer may be very large, return it modulo 109 + 7.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 */

class Solution
{
public:
    int sumCounts(std::vector<int>& nums)
    {
        // score of nums[i:j] = square of distinct count of nums[i:j]
        //
        // dp[i] = sum of scores of all subarrays ending at nums[i]
        // answer = dp[0] + dp[1] + ... + dp[n-1]
        //
        // let x = distinct count of a subarray A where A is ending at nums[i-1]
        // let A' = A.push_back(nums[i])
        // if nums[i] is not in A, then x' = distinct count of A' = x+1
        // score of A = x^2
        // score of A' = (x+1)^2 = x^2 + 2x + 1
        // delta = A' - A = 2x + 1
        //
        // case 1: nums[i] is not in nums[0:i-1]
        // - nums[i-1:i-1] <= nums[i], distinct count x1' = x1 + 1
        //   nums[i-2:i-1] <= nums[i], distinct count x2' = x2 + 1
        //   ...
        //   nums[0:i-1] <= nums[i], distinct count x_i' = xi + 1
        //   {} <= nums[i], single nums[i] is a valid subarray ending at nums[i]
        // - dp[i] = dp[i-1] + 2*(x1+...+xi) + i + 1
        //
        // case 2: let j = the last occurrence of nums[i] in nums[0:i-1]
        // - nums[i-1:i-1] <= nums[i], distinct count x1' = x1 + 1
        //   nums[i-2:i-1] <= nums[i], distinct count x2' = x2 + 1
        //   ...
        //   nums[j+1:i-1] <= nums[i], distinct count xp' = xp + 1, p = i-j-1
        //   {} <= nums[i], single nums[i] is a valid subarray ending at nums[i]
        // - dp[i] = dp[i-1] + 2*(x1+x2+...+xp) + (i-j-1) + 1
        //
        // let query(lo,hi) = distinct count of nums[hi:hi]
        //                    + distinct count of nums[hi-1:hi]
        //                    + distinct count of nums[hi-2:hi]
        //                    + ...
        //                    + distinct count of nums[lo:hi]
        //
        // let update(lo,hi) do the following work:
        // - distinct count of nums[hi:hi] += 1
        // - distinct count of nums[hi-1:hi] += 1
        // - ...
        // - distinct count of nums[lo:hi] += 1
        // - distinct counts of all subarrays ending at nums[i] increment by 1
        //
        // combine case 1 and case 2:
        // if nums[i] is not in nums[0:i-1], j = -1; otherwise, j = last occurrence of nums[i]
        // thus, dp[i] = dp[i-1] + 2 * query(j+1,i-1) + i - j
        // once we have dp[i], remember to update(j+1,i)
        constexpr long long kMod = 1e9 + 7;
        const int n = nums.size();
        data = std::vector<long long>(4 * n, 0);
        todo = std::vector<long long>(4 * n, 0);
        std::unordered_map<int, int> map; // <nums[i], j>, j = last occurrence of nums[i]
        long long dp = 0;
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            const int j = map.count(nums[i]) ? map[nums[i]] : -1;
            dp += i == 0 ? 1 : 2 * query(1, 1, n, j + 2, i) + i - j; // arguments are 1-indexed
            update(1, 1, n, j + 2, i + 1, 1); // including nums[i:i], arguments are 1-indexed
            result = (result + dp) % kMod;
            map[nums[i]] = i;
        }
        return result;
    }

private:
    std::vector<long long> data; // distinct count of each subarray, subarray id is 1-indexed
    std::vector<long long> todo; // 1-indexed

    void add(int id, int lo, int hi, long long delta)
    {
        data[id] += delta * (hi - lo + 1);
        todo[id] += delta;
    }

    long long query(int id, int lo, int hi, int L, int R)
    {
        if (lo >= L && hi <= R)
            return data[id];

        const int mid = lo + (hi - lo) / 2;
        if (todo[id]) {
            add(2 * id, lo, mid, todo[id]);
            add(2 * id + 1, mid + 1, hi, todo[id]);
            todo[id] = 0;
        }
        long long sum = 0;
        if (mid >= L) {
            sum += query(2 * id, lo, mid, L, R);
        }
        if (mid + 1 <= R) {
            sum += query(2 * id + 1, mid + 1, hi, L, R);
        }
        return sum;
    }

    void update(int id, int lo, int hi, int L, int R, long long delta)
    {
        if (lo >= L && hi <= R) {
            add(id, lo, hi, delta);
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        if (todo[id]) {
            add(2 * id, lo, mid, todo[id]);
            add(2 * id + 1, mid + 1, hi, todo[id]);
            todo[id] = 0;
        }
        if (mid >= L) {
            update(2 * id, lo, mid, L, R, delta);
        }
        if (mid + 1 <= R) {
            update(2 * id + 1, mid + 1, hi, L, R, delta);
        }
        data[id] = data[2 * id] + data[2 * id + 1];
    }
};