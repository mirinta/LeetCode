#include <algorithm>
#include <vector>

/**
 * You want to build some obstacle courses. You are given a 0-indexed integer array "obstacles" of
 * length "n", where obstacles[i] describes the height of the ith obstacle.
 *
 * For every index i between 0 and n - 1 (inclusive), find the length of the longest obstacle course
 * in obstacles such that:
 *
 * - You choose any number of obstacles between 0 and i inclusive.
 *
 * - You must include the ith obstacle in the course.
 *
 * - You must put the chosen obstacles in the same order as they appear in obstacles.
 *
 * - Every obstacle (expect the first) is taller than or the same height as the obstacle immediately
 * before it.
 *
 * Return an array "ans" of length n, where ans[i] is the length of the longest obstacle course for
 * index i as described above.
 */

class Solution
{
public:
    // similar to LC 300, this problem is to find the longest non-decreasing subsequence
    // initialize a non-decreasing array with the same size, arr = [X, ..., X], where X = INT_MAX
    // for each nums[i]
    // - find the first position j in arr s.t. arr[j] > nums[i]
    // - update arr[j] = nums[i]
    // - record subsequence length = j + 1
    // Example: let input nums = [3, 1, 5, 6, 4, 2], arr = [X, X, X, X, X, X]
    // - nums[0] = 3, find j = 0, arr = [3, X, X, X, X, X], subsequence length = 1;
    // - nums[1] = 1, find j = 0, arr = [1, X, X, X, X, X], subsequence length = 1;
    // - nums[2] = 5, find j = 1, arr = [1, 5, X, X, X, X], subsequence length = 2;
    // - nums[3] = 6, find j = 2, arr = [1, 5, 6, X, X, X], subsequence length = 3;
    // - nums[4] = 4, find j = 1, arr = [1, 4, 6, X, X, X], subsequence length = 2;
    // - nums[5] = 2, find j = 1, arr = [1, 2, 6, X, X, X], subsequence length = 2;
    // - put all subsequence length above in a vector and return, [1, 1, 2, 3, 2, 2]
    std::vector<int> longestObstacleCourseAtEachPosition(std::vector<int>& obstacles)
    {
        if (obstacles.empty())
            return {};

        std::vector<int> result;
        // disadvantage: waste of space in arr
        // std::vector<int> arr(obstacles.size(), INT_MAX);
        // for (const auto& val : obstacles) {
        //     const auto j = upperBound(arr, val);
        //     if (j < 0)
        //         continue;

        //     result.push_back(j + 1);
        //     arr[j] = val;
        // }
        std::vector<int> arr; // maintain in non-decreasing order
        for (const auto& val : obstacles) {
            if (arr.empty() || val >= arr.back()) {
                arr.push_back(val);
                result.push_back(arr.size());
            } else {
                auto iter = std::upper_bound(arr.begin(), arr.end(), val);
                if (iter == arr.end())
                    continue;

                *iter = val;
                result.push_back(iter - arr.begin() + 1);
            }
        }
        return result;
    }

private:
    // return the first position j s.t. arr[j] > val
    // the input array is sorted in non-decreasing order
    int upperBound(std::vector<int>& arr, int val)
    {
        if (arr.empty())
            return -1;

        int left = 0;
        int right = arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= val) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left == arr.size() ? -1 : left;
    }
};