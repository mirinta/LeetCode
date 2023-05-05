#include <utility>
#include <vector>

/**
 * Given an integer array "nums", move all the even integers at the beginning of the array followed
 * by all the odd integers.
 *
 * Return any array that satisfies this condition.
 */

class Solution
{
public:
    std::vector<int> sortArrayByParity(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        std::vector<int> result(nums);
        const auto size = result.size();
        int low = 0;
        int high = size - 1;
        while (true) {
            while (low < size && result[low] % 2 == 0) {
                low++;
            }
            while (high >= 0 && result[high] % 2 != 0) {
                high--;
            }
            if (low >= high)
                break;

            std::swap(result[low++], result[high--]);
        }
        return result;
    }
};