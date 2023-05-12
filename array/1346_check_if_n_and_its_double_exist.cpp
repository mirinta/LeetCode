#include <unordered_set>
#include <vector>

/**
 * Given an array "arr" of integers, check if there exist two indices i and j such that:
 *
 * - i != j
 *
 * - 0 <= i, j < arr.length
 *
 * - arr[i] == arr[j] * 2
 */

class Solution
{
public:
    bool checkIfExist(std::vector<int>& arr)
    {
        if (arr.size() < 2)
            return false;

        // approach 1: hash set
        // std::unordered_set<int> set;
        // for (const auto& i : arr) {
        //     if (set.count(2 * i))
        //         return true;

        //     if (i % 2 == 0 && set.count(i / 2))
        //         return true;

        //     set.insert(i);
        // }
        // approach 2: traverse
        for (size_t i = 0; i < arr.size() - 1; ++i) {
            for (size_t j = 0; j < arr.size(); ++j) {
                if (i != j && arr[i] == arr[j] * 2)
                    return true;
            }
        }
        return false;
    }
};