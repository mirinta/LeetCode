#include <queue>
#include <unordered_set>
#include <vector>

/**
 * You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.
 *
 * Define a pair (u, v) which consists of one element from the first array and one element from the
 * second array.
 *
 * Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.
 *
 * ! 1 <= nums1.length, nums2.length <= 10^5
 * ! -10^9 <= nums1[i], nums2[i] <= 10^9
 * ! nums1 and nums2 both are sorted in ascending order.
 * ! 1 <= k <= 10^4
 */

class Solution
{
public:
    std::vector<std::vector<int>> kSmallestPairs(std::vector<int>& nums1, std::vector<int>& nums2,
                                                 int k)
    {
        auto comp = [&nums1, &nums2](const auto& pair1, const auto& pair2) -> bool {
            return nums1[pair1.first] + nums2[pair1.second] >
                   nums1[pair2.first] + nums2[pair2.second];
        };
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp)>
            pq(comp);
        pq.push({0, 0});
        std::unordered_set<int> visited;
        visited.insert(0);
        std::vector<std::vector<int>> result;
        while (!pq.empty() && k > 0) {
            const auto [i, j] = pq.top();
            pq.pop();
            if (j + 1 < nums2.size()) {
                pq.push({i, j + 1});
            }
            if (i + 1 < nums1.size() && !visited.count(i + 1)) {
                pq.push({i + 1, j});
                visited.insert(i + 1);
            }
            result.push_back({nums1[i], nums2[j]});
            k--;
        }
        return result;
    }
};
// nums1 = [1,1,2], nums2 = [1,2,3]
// - use nums1[0] and nums2[j]: sum(1,1) -> sum(1,2) -> sum(1,3)
// - use nums1[1] and nums2[j]: sum(1,1) -> sum(1,2) -> sum(1,3)
// - use nums1[2] and nums2[j]: sum(2,1) -> sum(2,2) -> sum(2,3)
