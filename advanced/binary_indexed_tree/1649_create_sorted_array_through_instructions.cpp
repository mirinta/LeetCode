#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Given an integer array instructions, you are asked to create a sorted array from the elements in
 * instructions. You start with an empty container nums. For each element from left to right in
 * instructions, insert it into nums. The cost of each insertion is the minimum of the following:
 *
 * - The number of elements currently in nums that are strictly less than instructions[i].
 *
 * - The number of elements currently in nums that are strictly greater than instructions[i].
 *
 * For example, if inserting element 3 into nums = [1,2,3,5], the cost of insertion is min(2, 1)
 * (elements 1 and 2 are less than 3, element 5 is greater than 3) and nums will become [1,2,3,3,5].
 *
 * Return the total cost to insert all elements from instructions into nums. Since the answer may be
 * large, return it modulo 10^9 + 7.
 *
 * ! 1 <= instructions.length <= 10^5
 * ! 1 <= instructions[i] <= 10^5
 */

class BinaryIndexedTree
{
public:
    explicit BinaryIndexedTree(int n) : tree(n + 1, 0) {}

    void add(int i, int delta)
    {
        for (; i < tree.size(); i += lowbit(i)) {
            tree[i] += delta;
        }
    }

    int query(int left, int right) { return presum(right) - presum(left - 1); }

private:
    int presum(int i)
    {
        int sum = 0;
        for (; i > 0; i -= lowbit(i)) {
            sum += tree[i];
        }
        return sum;
    }

    int lowbit(int i) { return i & -i; }

private:
    std::vector<int> tree;
};

class Solution
{
public:
    int createSortedArray(std::vector<int>& instructions)
    {
        constexpr int kMod = 1e9 + 7;
        const int n = instructions.size();
        std::unordered_set<int> set(instructions.begin(), instructions.end());
        std::vector<int> uniques(set.begin(), set.end());
        std::sort(uniques.begin(), uniques.end());
        std::unordered_map<int, int> map;
        for (int i = 0; i < uniques.size(); ++i) {
            map[uniques[i]] = i;
        }
        BinaryIndexedTree tree(uniques.size());
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            const int cost1 = i - tree.query(map[instructions[i]] + 1, map[uniques.back()] + 1);
            const int cost2 = i - tree.query(map[uniques.front()] + 1, map[instructions[i]] + 1);
            result = (result + std::min(cost1, cost2)) % kMod;
            tree.add(map[instructions[i]] + 1, 1);
        }
        return result;
    }
};