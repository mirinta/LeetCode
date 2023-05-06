#include <queue>
#include <vector>

/**
 * Given a binary array "nums", return the maximum number of consecutive 1's in the array if you can
 * flip at most one 0.
 *
 * ! nums[i] is either 0 or 1
 *
 * ! Follow up:
 * What if the input numbers come in one by one as an infinite stream? In other words, you can't
 * store all numbers coming from the stream as it's too large to hold in memory. Could you solve it
 * efficiently?
 */

class Solution
{
public:
    // version 1: FIFO queue
    // int findMaxConsecutiveOnes(std::vector<int>& nums)
    // {
    //     if (nums.empty())
    //         return 0;

    //     int result = 0;
    //     int countZero = 0;
    //     std::queue<int> queue;
    //     for (const auto& val : nums) {
    //         queue.push(val);
    //         if (val == 0) {
    //             countZero++;
    //         }
    //         while (!queue.empty() && countZero > 1) {
    //             if (queue.front() == 0) {
    //                 countZero--;
    //             }
    //             queue.pop();
    //         }
    //         result = std::max<int>(result, queue.size());
    //     }
    //     return result;
    // }
    // version 2: sliding window
    int findMaxConsecutiveOnes(std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        int result = 0;
        int countZero = 0;
        int left = 0;
        int right = 0;
        // sliding window, elements in range [left, right)
        while (right < nums.size()) {
            if (nums[right++] == 0) {
                countZero++;
            }
            while (countZero > 1) {
                if (nums[left++] == 0) {
                    countZero--;
                }
            }
            result = std::max(result, right - left);
        }
        return result;
    }
};