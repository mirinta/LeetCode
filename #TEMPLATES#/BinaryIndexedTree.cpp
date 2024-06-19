#include <iostream>
#include <vector>

class BinaryIndexedTree
{
public:
    /**
     * ! @note n is the number of elements, i.e., n = nums.size()
     */
    explicit BinaryIndexedTree(int n) : tree(n + 1, 0) {}

    /**
     * @brief Increase the ith element by delta.
     *
     * ! @note i is 1-indexed.
     */
    void add(int i, long long delta)
    {
        if (!validate(i))
            return;

        while (i < tree.size()) {
            tree[i] += delta;
            i += lowbit(i);
        }
    }

    /**
     * @brief Return the sum of nums[left:right], where left <= right.
     *
     * ! @note left and right are 1-indexed.
     */
    long long query(int left, int right)
    {
        if (left > right || !validate(left) || !validate(right))
            return 0;

        return presum(right) - presum(left - 1);
    }

private:
    int lowbit(int i) { return i & (-i); }

    bool validate(int i) const { return i >= 1 && i < tree.size(); }

    // Return the sum of tree[0:i]
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
    std::vector<long long> tree; // ! 1-indexed
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