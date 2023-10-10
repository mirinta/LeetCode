#include <algorithm>
#include <unordered_set>
#include <vector>

/**
 * You are given an integer array nums. In one operation, you can replace any element in nums with
 * any integer.
 *
 * nums is considered continuous if both of the following conditions are fulfilled:
 *
 * - All elements in nums are unique.
 *
 * - The difference between the maximum element and the minimum element in nums equals
 * nums.length 1.
 *
 * For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6] is not continuous.
 *
 * Return the minimum number of operations to make nums continuous.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution
{
public:
    int minOperations(std::vector<int>& nums)
    {
        // assume x is the min value of an array with length N
        // if the array is valid,
        // then its elements must be {X,X+1,X+2,...,X+N-1}
        // assume the array is sorted and values are unique
        // index: ... i ... ... j j+1 ... ... n-1
        // value:     I         J X ... ... ... X
        //            |<------->| |<-remaining->|
        // given I = nums[i] as the min value,
        // we want to find J = nums[j] such that J-I=N-1,
        // and put the remaining elements into the range [I,J]
        // - num of operations = num of remaining elements = n - num of elements already in the
        // range [I,J]
        // - num of elements already in the range [I,J] = j - i + 1
        // - it doesn't matter if J=N-1+I is not found,
        // we can change one of the remaining elements to be J
        // - sliding window: given i, increase j as long as J-I<=N-1
        const int n = nums.size();
        std::unordered_set<int> set(nums.begin(), nums.end()); // remove duplicates
        std::vector<int> unique(set.begin(), set.end());
        std::sort(unique.begin(), unique.end());
        int result = n; // max num of operations = each character of the given array is replaced
        for (int i = 0, j = 0; i < unique.size(); ++i) {
            while (j < unique.size() && unique[j] - unique[i] <= n - 1) {
                result = std::min(result, n - (j - i + 1));
                j++;
            }
        }
        return result;
    }
};
