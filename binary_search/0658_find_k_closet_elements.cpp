#include <vector>

/**
 * Given a sorted integer array "arr", two integers k and x, return the k closest integers to x in
 * the array. The result should also be sorted in ascending order.
 *
 * An integer a is closer to x than an integer b if:
 *
 * - |a - x| < |b - x|, or
 *
 * - |a - x| == |b - x| and a < b
 *
 * ! 1 <= k <= arr.length
 * ! 1 <= arr.length <= 10^4
 * ! arr is sorted in ascending order.
 * ! -10^4 <= arr[i], x <= 10^4
 */

class Solution
{
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x)
    {
        const int index = binarySearch(arr, x);
        // window, (left, right), both exclusive
        int left = index - 1;
        int right = index;
        for (int i = 0; i < k; ++i) {
            if (left < 0) {
                right++;
            } else if (right >= arr.size()) {
                left--;
            } else if (x - arr[left] <= arr[right] - x) {
                left--;
            } else {
                right++;
            }
        }
        std::vector<int> result;
        for (int i = left + 1; i <= right - 1; ++i) {
            result.push_back(arr[i]);
        }
        return result;
    }

private:
    // find the first index of target in nums,
    // if it is not in nums, return its insertion position
    int binarySearch(const std::vector<int>& nums, int target)
    {
        if (nums.empty())
            return 0;

        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] >= target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }
};