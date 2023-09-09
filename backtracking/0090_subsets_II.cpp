#include <algorithm>
#include <vector>

/**
 * Given an integer array "nums" that may contain duplicates, return all possible subsets (the power
 * set).
 *
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * ! 1 <= nums.length <= 10
 * ! -10 <= nums[i] <= 10
 */

class Solution
{
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        std::sort(nums.begin(), nums.end()); // arrange the duplicate values together
        Vec2D<int> result;
        Vec1D<int> subset;
        backtrack(result, subset, 0, nums);
        return result;
    }

private:
    template <typename T>
    using Vec2D = std::vector<std::vector<T>>;

    template <typename T>
    using Vec1D = std::vector<T>;

    void backtrack(Vec2D<int>& result, Vec1D<int>& subset, int index, const Vec1D<int>& nums)
    {
        result.push_back(subset);
        for (int i = index; i < nums.size(); ++i) {
            if (i > index && nums[i] == nums[i - 1])
                continue;

            subset.push_back(nums[i]);
            backtrack(result, subset, i + 1, nums);
            subset.pop_back();
        }
    }
};