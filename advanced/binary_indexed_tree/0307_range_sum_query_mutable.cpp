#include <vector>

/**
 * Given an integer array nums, handle multiple queries of the following types:
 *
 * 1. Update the value of an element in nums.
 *
 * 2. Calculate the sum of the elements of nums between indices left and right inclusive where left
 * <= right.
 *
 * Implement the NumArray class:
 *
 * - NumArray(int[] nums) Initializes the object with the integer array nums.
 *
 * - void update(int index, int val) Updates the value of nums[index] to be val.
 *
 * - int sumRange(int left, int right) Returns the sum of the elements of nums between indices left
 * and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 *
 * ! 1 <= nums.length <= 3 * 10^4
 * ! -100 <= nums[i] <= 100
 * ! 0 <= index < nums.length
 * ! -100 <= val <= 100
 * ! 0 <= left <= right < nums.length
 * ! At most 3 * 104 calls will be made to update and sumRange.
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

class NumArray
{
public:
    NumArray(std::vector<int>& nums) : nums(nums), tree(nums) {}

    void update(int index, int val)
    {
        tree.add(index + 1, val - nums[index]);
        nums[index] = val;
    }

    int sumRange(int left, int right) { return tree.query(left + 1, right + 1); }

private:
    std::vector<int> nums;
    BinaryIndexedTree tree;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
