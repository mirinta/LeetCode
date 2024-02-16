#include <numeric>
#include <unordered_map>
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
    // sliding window, TC = O(N), SC = O(1)
    int approach2(const std::vector<int>& nums, int x)
    {
        // 0 ... i-1 i ... j-1 j ... n-1
        // |<--A-->| |<--B-->| |<--C-->|
        // A = sum of nums[0:i-1]
        // B = sum of nums[i:j-1]
        // C = sum of nums[j:n-1]
        // total = A + B + C = nums[0:n-1]
        // if A + C = x, then B = total - x
        // num of operations = i + j = L - length of B
        // our goal is to find the longest subarray with sum = total - x
        const int n = nums.size();
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        int sum = 0;
        int length = INT_MIN;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += nums[right];
            while (left <= right && sum > total - x) {
                sum -= nums[left];
                left++;
            }
            if (sum == total - x) {
                length = std::max(length, right - left + 1);
            }
        }
        return length == INT_MIN ? -1 : n - length;
    }

    // prefix and suffix sum + hash map, TC = O(N), SC = O(N)
    int approach1(const std::vector<int>& nums, int x)
    {
        // let prefixSum[i] = sum of nums[0:i]
        // let suffixSum[j] = sum of nums[j:n-1]
        // if there exists i and j such that i < j
        // prefixSum[i] + suffixSum[j] = x,
        // then num of operations = i+1+n-j
        const int n = nums.size();
        std::unordered_map<int, int> map;
        int prefixSum = 0;
        for (int i = 0; i < n; ++i) {
            prefixSum += nums[i];
            map[prefixSum] = i;
        }
        // base case 1: prefixSum[p] = x, num of operations = i+1
        int result = INT_MAX;
        if (map.count(x)) {
            result = map[x] + 1;
        }
        // base case 2: suffixSum[q] = x, num of operations = n-q
        map[0] = -1;
        int suffixSum = 0;
        for (int j = n - 1; j >= 0; --j) {
            suffixSum += nums[j];
            const int target = x - suffixSum;
            if (map.count(target) && map[target] < j) {
                result = std::min(result, map[target] + 1 + n - j);
            }
        }
        return result == INT_MAX ? -1 : result;
    }
};