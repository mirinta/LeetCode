#include <vector>

/**
 * Given an integer array nums, return an array answer such that answer[i] is equal to the product
 * of all the elements of nums except nums[i].
 *
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 *
 * You must write an algorithm that runs in O(n) time and without using the division operation.
 *
 * ! 2 <= nums.length <= 10^5
 * ! -30 <= nums[i] <= 30
 * ! The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 */

class Solution
{
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) { return approach2(nums); }

private:
    // time O(n), space O(1)
    std::vector<int> approach2(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n, 1);
        for (int i = 1; i < n; ++i) {
            result[i] = result[i - 1] * nums[i - 1];
        }
        for (int i = n - 1, product = 1; i >= 0; --i) {
            result[i] *= product;
            product *= nums[i];
        }
        return result;
    }

    // time O(n), space O(n)
    std::vector<int> approach1(std::vector<int>& nums)
    {
        const int n = nums.size();
        // left[i]=nums[i-1]*nums[i-2]*...
        std::vector<int> left(n, 1);
        for (int i = 1; i < n; ++i) {
            left[i] = left[i - 1] * nums[i - 1];
        }
        // right[i]=nums[i+1]*nums[i+2]*...
        std::vector<int> right(n, 1);
        for (int i = n - 2; i >= 0; --i) {
            right[i] = right[i + 1] * nums[i + 1];
        }
        std::vector<int> result(n, 1);
        for (int i = 0; i < n; ++i) {
            result[i] = left[i] * right[i];
        }
        return result;
    }
};