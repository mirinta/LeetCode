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
    // two-pass, time O(N), space O(n)
    std::vector<int> approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n, 1);
        for (int i = 1; i < n; ++i) {
            result[i] = result[i - 1] * nums[i - 1];
        }
        for (int i = n - 1, rightProduct = 1; i >= 0; --i) {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }
        return result;
    }

    // three-pass, time O(N), space O(N)
    std::vector<int> approach1(const std::vector<int>& nums)
    {
        // X X X ... X X A X X X ... X X
        // |<-product->|   |<-product->|
        const int n = nums.size();
        std::vector<int> leftProduct(n, 1);
        std::vector<int> rightProduct(n, 1);
        for (int i = 1; i < n; ++i) {
            leftProduct[i] = leftProduct[i - 1] * nums[i - 1];
        }
        for (int i = n - 2; i >= 0; --i) {
            rightProduct[i] = rightProduct[i + 1] * nums[i + 1];
        }
        std::vector<int> result(n, 1);
        for (int i = 0; i < n; ++i) {
            result[i] = leftProduct[i] * rightProduct[i];
        }
        return result;
    }
};