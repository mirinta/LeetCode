#include <vector>

/**
 * Given n non-negative integers representing an elevation map where the width of each bar is 1,
 * compute how much water it can trap after raining.
 *
 * ! n == height.length
 * ! 1 <= n <= 2 * 10^4
 * ! 0 <= height[i] <= 10^5
 */

class Solution
{
public:
    int trap(std::vector<int>& height) { return approach2(height); }

private:
    // time O(N), space O(1)
    int approach2(const std::vector<int>& height)
    {
        const int n = height.size();
        int leftMax = 0;
        int rightMax = 0;
        int left = 0;
        int right = n - 1;
        int result = 0;
        while (left <= right) {
            leftMax = std::max(leftMax, height[left]);
            rightMax = std::max(rightMax, height[right]);
            if (leftMax < rightMax) {
                result += leftMax - height[left];
                left++;
            } else {
                result += rightMax - height[right];
                right--;
            }
        }
        return result;
    }

    // time O(N), space O(N)
    int approach1(const std::vector<int>& height)
    {
        const int n = height.size();
        std::vector<int> leftMax(n, height[0]);      // max height of height[0],...,height[i]
        std::vector<int> rightMax(n, height[n - 1]); // max height of height[i],...,height[n-1]
        for (int i = 1; i < n; ++i) {
            leftMax[i] = std::max(leftMax[i - 1], height[i]);
            rightMax[n - i - 1] = std::max(rightMax[n - i], height[n - i - 1]);
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += std::min(leftMax[i], rightMax[i]) - height[i];
        }
        return result;
    }
};