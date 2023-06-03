#include <utility>
#include <vector>

/**
 * Given an array "nums" with "n" objects colored red, white, or blue, sort them in-place so that
 * objects of the same color are adjacent, with the colors in the order red, white, and blue.
 *
 * We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
 *
 * You must solve this problem without using the library's sort function.
 *
 * ! n == nums.length
 * ! 1 <= n <= 300
 * ! nums[i] is either 0, 1, or 2.
 */

class Solution
{
public:
    void sortColors(vector<int>& nums)
    {
        if (nums.size() <= 1)
            return;

        // three-way partition, target value = 1
        int lt = 0;
        int i = 0;
        int gt = nums.size() - 1;
        while (i <= gt) {
            if (nums[i] < 1) {
                std::swap(nums[i++], nums[lt++]);
            } else if (nums[i] > 1) {
                std::swap(nums[i], nums[gt--]);
            } else {
                i++;
            }
        }
    }
};