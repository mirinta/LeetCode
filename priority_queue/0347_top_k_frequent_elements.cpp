#include <queue>
#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums and an integer k, return the k most frequent elements. You may return
 * the answer in any order.
 *
 * ! Your algorithm's time complexity must be better than O(nlogn), where n is the array's size.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 * ! k is in the range [1, the number of unique elements in the array].
 * ! It is guaranteed that the answer is unique.
 */

class Solution
{
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        std::priority_queue<Pair, std::vector<Pair>, Compare> pq;
        for (const auto& pair : map) {
            pq.push(pair);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        std::vector<int> result;
        result.reserve(pq.size());
        while (!pq.empty()) {
            result.emplace_back(pq.top().first);
            pq.pop();
        }
        return result;
    }

private:
    using Pair = std::pair<int, int>; // <val, freq>

    struct Compare
    {
        bool operator()(const Pair& p1, const Pair& p2) const { return p1.second > p2.second; }
    };
};
