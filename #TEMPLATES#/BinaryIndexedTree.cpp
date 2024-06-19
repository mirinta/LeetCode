#include <iostream>
#include <vector>

/**
 * BinaryIndexedTree(int n): n is the num of elements, i.e., n = nums.size()
 *
 * add(int i, long long delta): make nums[i] += delta, i is 1-indexed
 *
 * query(int left, int right): query the sum of nums[left:right], left and right are 1-indexed
 *
 * presum(int i): return the sum of nums[1:i], i is 1-indexed
 *
 * std::vector<long long> tree: a 1-indexed array
 */
class BinaryIndexedTree
{
public:
    explicit BinaryIndexedTree(int n) : tree(n + 1, 0) {}

    void add(int i, long long delta)
    {
        if (!validate(i))
            return;

        while (i < tree.size()) {
            tree[i] += delta;
            i += lowbit(i);
        }
    }

    long long query(int left, int right)
    {
        if (left > right || !validate(left) || !validate(right))
            return 0;

        return presum(right) - presum(left - 1);
    }

private:
    int lowbit(int i) { return i & (-i); }

    bool validate(int i) const { return i >= 1 && i < tree.size(); }

    long long presum(int i)
    {
        long long sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= lowbit(i);
        }
        return sum;
    }

private:
    std::vector<long long> tree;
};

int main()
{
    // example: query range sum
    std::vector<int> nums{1, 2, 3, 4};
    BinaryIndexedTree tree(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
        tree.add(i + 1, nums[i]);
    }
    std::cout << tree.query(2, 4) << '\n'; // 2+3+4=9
    tree.add(3, 5);                        // nums = [1,2,8,4]
    std::cout << tree.query(2, 4) << '\n'; // 2+8+4=14
    return 0;
}