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
        int result = 0;
        int left = 0;
        int right = height.size() - 1;
        int prefixMax = 0;
        int suffixMax = 0;
        while (left <= right) {
            prefixMax = std::max(prefixMax, height[left]);
            suffixMax = std::max(suffixMax, height[right]);
            if (prefixMax < suffixMax) {
                result += prefixMax - height[left];
                left++;
            } else {
                result += suffixMax - height[right];
                right--;
            }
        }
        return result;
    }

    // time O(N), space O(N)
    int approach1(const std::vector<int>& height)
    {
        const int n = height.size();
        std::vector<int> prefixMax(height);
        std::vector<int> suffixMax(height);
        for (int i = 1; i < n; ++i) {
            prefixMax[i] = std::max(prefixMax[i - 1], height[i]);
            suffixMax[n - i - 1] = std::max(suffixMax[n - i], height[n - i - 1]);
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += std::min(prefixMax[i], suffixMax[i]) - height[i];
        }
        return result;
    }
};