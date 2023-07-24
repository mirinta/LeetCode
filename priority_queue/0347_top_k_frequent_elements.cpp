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
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) { return approach2(nums, k); }

private:
    // quick-select
    std::vector<int> approach2(std::vector<int>& nums, int k)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        std::vector<int> unique;
        for (const auto& [val, frequency] : map) {
            unique.push_back(val);
        }
        const int rank = unique.size() - k;
        int lo = 0;
        int hi = unique.size() - 1;
        while (lo < hi) {
            const int pos = partition(lo, hi, unique, map);
            if (pos > rank) {
                hi = pos - 1;
            } else if (pos < rank) {
                lo = pos + 1;
            } else {
                break;
            }
        }
        return {unique.begin() + rank, unique.end()};
    }

    int partition(int lo, int hi, std::vector<int>& nums, const std::unordered_map<int, int>& map)
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
    std::vector<int> approach1(std::vector<int>& nums, int k)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        auto comp = [](const auto& p1, const auto& p2) -> bool { return p1.first > p2.first; };
        // min heap, <frequency, val>
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp)>
            pq(comp);
        for (const auto& [val, frequency] : map) {
            pq.push({frequency, val});
            if (pq.size() > k) {
                pq.pop();
            }
        }
        std::vector<int> result(std::min<size_t>(k, pq.size()), 0);
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] = pq.top().second;
            pq.pop();
        }
        return result;
    }
};
