#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given a 1-indexed array of integers nums of length n.
 *
 * We define a function greaterCount such that greaterCount(arr, val) returns the number of elements
 * in arr that are strictly greater than val.
 *
 * You need to distribute all the elements of nums between two arrays arr1 and arr2 using n
 * operations. In the first operation, append nums[1] to arr1. In the second operation, append
 * nums[2] to arr2. Afterwards, in the ith operation:
 *
 * - If greaterCount(arr1, nums[i]) > greaterCount(arr2, nums[i]), append nums[i] to arr1.
 *
 * - If greaterCount(arr1, nums[i]) < greaterCount(arr2, nums[i]), append nums[i] to arr2.
 *
 * - If greaterCount(arr1, nums[i]) == greaterCount(arr2, nums[i]), append nums[i] to the array with
 * a lesser number of elements.
 *
 * - If there is still a tie, append nums[i] to arr1.
 *
 * The array result is formed by concatenating the arrays arr1 and arr2. For example, if arr1 ==
 * [1,2,3] and arr2 == [4,5,6], then result = [1,2,3,4,5,6].
 *
 * Return the integer array result.
 *
 * ! 3 <= n <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class BinaryIndexedTree
{
public:
    explicit BinaryIndexedTree(int n) : tree(n + 1, 0){};

    void add(int i, int delta)
    {
        for (; i < tree.size(); i += lowbit(i)) {
            tree[i] += delta;
        }
    }

    int query(int left, int right) { return presum(right) - presum(left - 1); }

private:
    int lowbit(int i) { return i & -i; }

    int presum(int i)
    {
        int sum = 0;
        for (; i > 0; i -= lowbit(i)) {
            sum += tree[i];
        }
        return sum;
    }

private:
    std::vector<int> tree;
};

class Solution
{
public:
    std::vector<int> resultArray(std::vector<int>& nums)
    {
        std::unordered_set<int> set(nums.begin(), nums.end());
        std::vector<int> unique(set.begin(), set.end());
        std::sort(unique.begin(), unique.end());
        BinaryIndexedTree tree1(unique.size());
        BinaryIndexedTree tree2(unique.size());
        std::unordered_map<int, int> map;
        for (int i = 0; i < unique.size(); ++i) {
            map[unique[i]] = i;
        }
        std::vector<int> v1{nums[0]};
        tree1.add(map[nums[0]] + 1, 1);
        std::vector<int> v2{nums[1]};
        tree2.add(map[nums[1]] + 1, 1);
        for (int i = 2; i < nums.size(); ++i) {
            const int count1 = v1.size() - tree1.query(1, map[nums[i]] + 1);
            const int count2 = v2.size() - tree2.query(1, map[nums[i]] + 1);
            if (count1 < count2 || (count1 == count2 && v2.size() < v1.size())) {
                v2.push_back(nums[i]);
                tree2.add(map[nums[i]] + 1, 1);
            } else {
                v1.push_back(nums[i]);
                tree1.add(map[nums[i]] + 1, 1);
            }
        }
        v1.insert(v1.end(), v2.begin(), v2.end());
        return v1;
    }
};