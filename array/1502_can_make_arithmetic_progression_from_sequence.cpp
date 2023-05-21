#include <algorithm>
#include <vector>

/**
 * A sequence of numbers is called an arithmetic progression if the difference between any two
 * consecutive elements is the same.
 *
 * Given an array of numbers "arr", return true if the array can be rearranged to from an arithmetic
 * progression. Otherwise, return false;
 */

class Solution
{
public:
    bool canMakeArithmeticProgression(std::vector<int>& arr)
    {
        if (arr.size() < 2)
            return false;

        std::sort(arr.begin(), arr.end());
        for (size_t i = 1; i < arr.size() - 1; ++i) {
            if (arr[i] - arr[i - 1] != arr[i + 1] - arr[i])
                return false;
        }
        return true;
    }
};