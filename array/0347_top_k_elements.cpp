#include <queue>
#include <unordered_map>
#include <vector>

/**
 * Given an integer array "nums" and an integer "k", return the "k" most frequent elements. You may
 * return the answer in any order.
 *
 * ! k is 1-indexed.
 * ! Your algorithm's time complexity must be better than O(nlogn), where n is the array's size.
 */

class Solution
{
public:
    std::vector<int> topKFrequent(const std::vector<int>& nums, int k)
    {
        if (nums.empty() || k < 1)
            return {};

        std::unordered_map<int, int> map; // value to frequency
        for (const auto& i : nums) {
            map[i]++;
        }
        // min priority queue
        using Pair = std::pair<int, int>; // <value, frequency>
        auto comp = [](const Pair& p1, const Pair& p2) { return p1.second > p2.second; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comp)> minHeap(comp);
        for (const auto& valToFreq : map) {
            minHeap.push({valToFreq.first, valToFreq.second});
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        std::vector<int> result(k, 0);
        for (int i = k - 1; i >= 0 && !minHeap.empty(); i--) {
            result[i] = minHeap.top().first;
            minHeap.pop();
        }
        return result;
    }
};