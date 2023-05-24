#include <climits>
#include <cstddef>
#include <queue>
#include <vector>

/**
 * You are given two 0-indexed integer arrays "nums1" and "nums2" of equal length "n" and a positive
 * integer "k". You must choose a subsequence of indices from "nums1" of length "k".
 *
 * For chosen indices i0, i1, ..., ik-1, your score is defined as:
 *
 * - The sum of the selected elements from "nums1" multiplied with the minimum of the selected
 * elements from "nums2".
 *
 * - It can defined simply as: (nums1[i0] + nums1[i1] + ... + nums1[ik-1]) * min(nums2[i0],
 * nums2[i1], ..., nums2[ik-1]).
 *
 * Return the maximum possible score.
 *
 * A subsequence of indices of an array is a set that can be derived from the set {0, 1, ..., n-1}
 * by deleting some or no elements.
 *
 * ! n == nums1.length == nums2.length
 * ! 1 <= n <= 10^5
 * ! 0 <= nums1[i], nums2[j] <= 105
 * ! 1 <= k <= n
 */

class Solution
{
public:
    long long maxScore(const std::vector<int>& nums1, const std::vector<int>& nums2, int k)
    {
        const auto n = nums1.size();
        std::vector<std::pair<int, int>> pairs(n, {0, 0}); // <nums2[i], nums1[i]>
        for (size_t i = 0; i < n; ++i) {
            pairs[i].first = nums2[i];
            pairs[i].second = nums1[i];
        }
        // sort nums2 in ascending order
        std::sort(pairs.rbegin(), pairs.rend());
        // maintain a min heap to find out top K nums1[i]
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        long long score = 0;
        long long sum = 0;
        long long min = INT_MAX;
        for (const auto& pair : pairs) {
            min = pair.first;
            sum += pair.second;
            pq.push(pair.second);
            if (pq.size() > k) {
                sum -= pq.top();
                pq.pop();
            }
            if (pq.size() == k) {
                score = std::max(score, sum * min);
            }
        }
        return score;
    }
};
