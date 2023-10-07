#include <numeric>
#include <vector>

/**
 * You are given an integer array nums and an integer x. In one operation, you can either remove the
 * leftmost or the rightmost element from the array nums and subtract its value from x. Note that
 * this modifies the array for future operations.
 *
 * Return the minimum number of operations to reduce x to exactly 0 if it is possible, otherwise,
 * return -1.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^4
 * ! 1 <= x <= 10^9
 */

class Solution
{
public:
    int minOperations(std::vector<int>& nums, int x) { return approach2(nums, x); }

private:
    // sliding window, time O(N), space O(1)
    int approach2(const std::vector<int>& nums, int k)
    {
        // 0 ... ... i i+1 ... j-1 j ... ... n-1
        // |<-part1->| |<-part3->| |<--part2-->|
        // part1 = nums[0] + ... + nums[i]
        // part2 = nums[j] + ... + nums[n-1]
        // part3 = nums[i+1] + ... + nums[j-1]
        // total_sum = part1 + part2 + part3
        // if part1 + part2 = x, then part3 = total_sum - x
        // then num of operations to make up x = n - part3.size()
        // thus, our goal is max(part3.size()) where sum of part3 is x
        const int n = nums.size();
        const int target = std::accumulate(nums.begin(), nums.end(), 0) - k;
        int maxWindowSize = -1;
        int windowSum = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            windowSum += nums[right];
            while (left <= right && windowSum > target) {
                windowSum -= nums[left++];
            }
            if (windowSum == target) {
                maxWindowSize = std::max(maxWindowSize, right - left + 1);
            }
        }
        return maxWindowSize == -1 ? -1 : n - maxWindowSize;
    }

    // prefix sum + binary search, time O(NlogN), space O(N)
    int approach1(const std::vector<int>& nums, int x)
    {
        const int n = nums.size();
        std::vector<int> prefix(1 + n, 0); // prefix[i]=nums[0]+...+nums[i-1]
        std::vector<int> suffix(1 + n, 0); // suffix[i]=nums[n-1]+...+nums[n-i]
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + nums[i - 1];
            suffix[i] = suffix[i - 1] + nums[n - i];
        }
        // since nums[i] >=1, then both prefix and suffix are strictly increasing
        int result = INT_MAX;
        for (int i = 0; i <= n; ++i) {
            const int target = x - prefix[i];
            if (target < 0)
                break;

            const int j = binarySearch(0, n - i, target, suffix);
            if (j != -1) {
                result = std::min(result, i + j);
            }
        }
        return result == INT_MAX ? -1 : result;
    }

    int binarySearch(int lo, int hi, int target, const std::vector<int>& nums)
    {
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target)
                return mid;

            if (nums[mid] > target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return -1;
    }
};