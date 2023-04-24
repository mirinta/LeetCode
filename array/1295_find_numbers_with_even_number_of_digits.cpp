#include <vector>

/**
 * Given an array "nums" of integers, return how many of them contain an even number of digits.
 */

class Solution
{
public:
    int findNumbers(const std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        int result = 0;
        for (const auto& i : nums) {
            if (digits(i) % 2 == 0) {
                result++;
            }
        }
        return result;
    }

private:
    int digits(int val)
    {
        int count = 1;
        while (val / 10) {
            count++;
            val /= 10;
        }
        return count;
    }
};