#include <cstddef>
#include <unordered_map>
#include <vector>

/**
 * Given an integer array "nums", return an integer array "counts" where "counts[i]" is the number
 * of smaller elements to the right of "nums[i]".
 */

class Solution
{
public:
    // Example: [5, 2, 6, 1]
    // During merge sort, the array is break into many sub-arrays
    // - [5, 2, 6, 1] -> [5, 2] and [6, 1]
    // - [5, 2] -> [5] and [2]
    // - [6, 1] -> [6] and [1]
    // During the process of merge two sorted array, say merge [2, 5] and [1, 6]
    //   2     5     1      6
    // low     I     mid+1  J (high)
    // When assigning val[I] to the sorted array,
    // the number of smaller values to the right of val[I] is J - mid - 1.
    std::vector<int> countSmaller(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        const auto size = nums.size();
        auxiliary.clear();
        auxiliary.resize(size);
        result.clear();
        result.resize(size, 0);
        std::vector<Pair> pairs;
        for (size_t i = 0; i < size; ++i) {
            pairs.emplace_back(nums[i], i);
        }
        mergeSort(pairs, 0, size - 1);
        return result;
    }

private:
    using Pair = std::pair<int, int>; // value and its original index
    std::vector<Pair> auxiliary;
    std::vector<int> result;

    void mergeSort(std::vector<Pair>& pairs, int low, int high)
    {
        if (low >= high)
            return;

        int mid = low + (high - low) / 2;
        mergeSort(pairs, low, mid);
        mergeSort(pairs, mid + 1, high);
        merge(pairs, low, mid, high);
    }

    // merge two sorted sub-array, [low, mid] and [mid + 1, high]
    void merge(std::vector<Pair>& pairs, int low, int mid, int high)
    {
        for (size_t i = low; i <= high; ++i) {
            auxiliary[i] = pairs[i];
        }
        for (size_t i = low, j = mid + 1, k = low; k <= high; ++k) {
            if (i > mid) {
                pairs[k] = auxiliary[j++];
                continue;
            }
            if (j > high) {
                pairs[k] = auxiliary[i++];
                result[pairs[k].second] += j - mid - 1;
                continue;
            }
            if (auxiliary[i].first > auxiliary[j].first) {
                pairs[k] = auxiliary[j++];
            } else {
                pairs[k] = auxiliary[i++];
                result[pairs[k].second] += j - mid - 1;
            }
        }
    }
};