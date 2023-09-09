#include <vector>

/**
 * Given an array "nums" of distinct integers, return all the possible permutations. You can return
 * the answer in any order.
 *
 * ! 1 <= nums.length <= 6
 * ! -10 <= nums[i] <= 10
 * ! All the integers of nums are unique.
 */

class Solution
{
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        Vec2D<int> result;
        Vec1D<int> permutation;
        Vec1D<bool> visited(nums.size(), false);
        backtrack(result, permutation, visited, nums);
        return result;
    }

private:
    template <typename T>
    using Vec1D = std::vector<T>;

    template <typename T>
    using Vec2D = std::vector<std::vector<T>>;

    void backtrack(Vec2D<int>& result, Vec1D<int>& permutation, Vec1D<bool>& visited,
                   const Vec1D<int>& nums)
    {
        if (permutation.size() == nums.size()) {
            result.push_back(permutation);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (visited[i])
                continue;

            visited[i] = true;
            permutation.push_back(nums[i]);
            backtrack(result, permutation, visited, nums);
            permutation.pop_back();
            visited[i] = false;
        }
    }
};