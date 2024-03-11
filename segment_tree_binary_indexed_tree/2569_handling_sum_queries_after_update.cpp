#include <numeric>
#include <vector>

/**
 * You are given two 0-indexed arrays nums1 and nums2 and a 2D array queries of queries. There are
 * three types of queries:
 *
 * 1. For a query of type 1, queries[i] = [1, l, r]. Flip the values from 0 to 1 and from 1 to 0 in
 * nums1 from index l to index r. Both l and r are 0-indexed.
 *
 * 2. For a query of type 2, queries[i] = [2, p, 0]. For every index 0 <= i < n, set nums2[i] =
 * nums2[i] + nums1[i] * p.
 *
 * 3. For a query of type 3, queries[i] = [3, 0, 0]. Find the sum of the elements in nums2.
 *
 * Return an array containing all the answers to the third type queries.
 *
 * ! 1 <= nums1.length,nums2.length <= 10^5
 * ! nums1.length = nums2.length
 * ! 1 <= queries.length <= 10^5
 * ! queries[i].length = 3
 * ! 0 <= l <= r <= nums1.length - 1
 * ! 0 <= p <= 10^6
 * ! 0 <= nums1[i] <= 1
 * ! 0 <= nums2[i] <= 10^9
 */

class Solution
{
public:
    std::vector<long long> handleQuery(std::vector<int>& nums1, std::vector<int>& nums2,
                                       std::vector<std::vector<int>>& queries)
    {
        const int n = nums1.size();
        long long sum = std::accumulate(nums2.begin(), nums2.end(), 0LL);
        data = std::vector<long long>(4 * n, 0);
        todo = std::vector<bool>(4 * n, false);
        build(1, 1, n, nums1);
        std::vector<long long> result;
        for (const auto& q : queries) {
            if (q[0] == 1) {
                const int L = q[1] + 1; // to 1-indexed
                const int R = q[2] + 1; // to 1-indexed
                update(1, 1, n, L, R);
            } else if (q[0] == 2) {
                sum += data[1] * q[1];
            } else {
                result.push_back(sum);
            }
        }
        return result;
    }

private:
    std::vector<long long> data; // data[i] = num of 1's of the ith range of nums1, 1-indexed
    std::vector<bool> todo;      // lazy tags, do flip or not, 1-indexed

    void build(int id, int lo, int hi, const std::vector<int>& nums1)
    {
        if (lo == hi) {
            data[id] = nums1[lo - 1];
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        build(2 * id, lo, mid, nums1);
        build(2 * id + 1, mid + 1, hi, nums1);
        data[id] = data[2 * id] + data[2 * id + 1];
    }

    void flip(int id, int lo, int hi)
    {
        // flip [lo,hi], all 1's change to 0's
        data[id] = hi - lo + 1 - data[id];
        todo[id] = !todo[id];
    }

    void update(int id, int lo, int hi, int L, int R)
    {
        // L ... lo ... hi ... R
        if (lo >= L && hi <= R) {
            flip(id, lo, hi);
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        if (todo[id]) {
            flip(2 * id, lo, mid);
            flip(2 * id + 1, mid + 1, hi);
            todo[id] = false;
        }
        if (mid >= L) {
            update(2 * id, lo, mid, L, R);
        }
        if (mid + 1 <= R) {
            update(2 * id + 1, mid + 1, hi, L, R);
        }
        data[id] = data[2 * id] + data[2 * id + 1];
    }
};