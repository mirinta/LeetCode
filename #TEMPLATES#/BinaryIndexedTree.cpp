#include <vector>

/**
 * The following BIT is used to query range sums and update elements.
 */
class BinaryIndexedTree
{
public:
    explicit BinaryIndexedTree(const std::vector<int>& nums) : tree(nums.size() + 1, 0)
    {
        for (int i = 1; i <= nums.size(); ++i) {
            add(i, nums[i - 1]);
        }
    }

    /**
     * @brief Update nums[i] = nums[i] + delta
     *
     * @note i is 1-indexed.
     */
    void add(int i, int delta)
    {
        for (; i < tree.size(); i += lowbit(i)) {
            tree[i] += delta;
        }
    }

    /**
     * @brief Return sum of nums[left:right], where left <= right.
     *
     * @note left and right are 1-indexed.
     */
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

    int lowbit(int i) { return i & (-i); }

private:
    std::vector<int> tree; // 1-indexed
};