#include <queue>
#include <ranges>
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
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) { return approach2(nums, k); }

private:
    // quick-select (two-way partition)
    std::vector<int> approach2(std::vector<int>& nums, int k)
    {
        std::unordered_map<int, int> map; // val to frequency
        for (const auto& val : nums) {
            map[val]++;
        }
        std::vector<int> unique;
        unique.reserve(map.size());
        for (const auto& pair : map) {
            unique.push_back(pair.first);
        }
        int rank = unique.size() - k;
        int lo = 0;
        int hi = unique.size() - 1;
        while (lo < hi && rank) {
            const int j = partition(unique, lo, hi, map);
            if (rank < j) {
                hi = j - 1;
            } else if (rank > j) {
                lo = j + 1;
            } else {
                break;
            }
        }
        return {unique.begin() + rank, unique.end()};
    }

    int partition(std::vector<int>& nums, int lo, int hi, const std::unordered_map<int, int>& map)
    {
        const int pivot = map.at(nums[lo]);
        int i = lo + 1;
        int j = hi;
        while (true) {
            while (i <= hi && map.at(nums[i]) <= pivot) {
                i++;
            }
            while (j >= lo && map.at(nums[j]) > pivot) {
                j--;
            }
            if (i >= j)
                break;

            std::swap(nums[i], nums[j]);
        }
        std::swap(nums[lo], nums[j]);
        return j;
    }

    // priority queue
    std::vector<int> approach1(const std::vector<int>& nums, int k)
    {
        std::unordered_map<int, int> map; // val to frequency
        for (const auto& val : nums) {
            map[val]++;
        }
        using Pair = std::pair<int, int>; // val, frequency
        auto comparator = [](const auto& p1, const auto& p2) {
            return p1.second == p2.second ? p1.first > p2.first : p1.second > p2.second;
        };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(
            comparator); // min heap
        for (const auto& [val, freq] : map) {
            pq.emplace(val, freq);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        std::vector<int> result(std::min<size_t>(k, pq.size()));
        for (auto& iter : std::ranges::reverse_view(result)) {
            iter = pq.top().first;
            pq.pop();
        }
        return result;
    }
};
