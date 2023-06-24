#include <vector>

/**
 * 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
 *
 * 你可以假设数组是非空的，并且给定的数组总是存在多数元素。
 *
 * 1 <= 数组长度 <= 50000
 *
 * ! 本题与LC 169相同。
 */

class Solution
{
public:
    int majorityElement(std::vector<int>& nums)
    {
        // 方法1：quick-select找出第n/2大的数
        // 方法2：X的出现频率超过一半，其余数字的频率之和小于一半，
        // 遍历数组，统计票数，X的票数+1，非X的票数-1。
        int target = 0;
        int count = 0;
        for (const auto& val : nums) {
            if (count == 0) {
                target = val;
                count = 1;
            } else if (val == target) {
                count++;
            } else {
                count--;
            }
        }
        return target;
    }
};
