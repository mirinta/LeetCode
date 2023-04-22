#include <random>
#include <vector>

/**
 * You are given a 0-indexed array of positive integers "w" where "w[i]" describes the weight of the
 * "i"th index.
 *
 * You need to implement the function "pickIndex()", which randomly picks an index in the range "[0,
 * w.length - 1]" and returns it. The probability of picking an index "i" is "w[i] / sum(w)".
 *
 * Example:
 * If w = [1, 3], the probability of picking index "0" is 1 / (1 + 3) = 0.25, and the
 * probability of picking index "1" is 3 / (1 + 3) = 0.75.
 */

// INTUITION:
// Let weights = [4, 3, 2, 1].
// Throw a needle into the following line:
// - if the needle is dropped in the line segment [1, 4], then pickIndex() returns 0;
// - if the needle is dropped in the line segment [5, 7], then pickIndex() returns 1.
//
//      0 0 0 0 1 1 1 2 2 3 <- indices of "weights"
// START|-|-|-|-|-|-|-|-|-|END
//      1 2 3 4 5 6 7 8 9 10
//
// 1. generate the prefix sums, preSums = [0, weights[0], weights[0] + weights[1], ...];
// 2. randomly pick an integer X in range [1, TOTAL_SUM], TOTAL_SUM = preSums.back();
// 3. find the minimum index I, s.t. preSums[I] >= X
//
// Randomly pick integer: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

class Solution
{
private:
    static std::vector<int> createPreSums(const std::vector<int>& w)
    {
        std::vector<int> preSums(w.size() + 1, 0);
        for (size_t i = 0; i < w.size(); ++i) {
            preSums[i + 1] = w[i] + preSums[i];
        }
        return preSums;
    }
    int randomNumber() { return _dist(_gen); }

    std::vector<int> _preSums;
    std::uniform_int_distribution<int> _dist;
    std::random_device _rd;
    std::mt19937 _gen;

public:
    Solution(const std::vector<int>& w)
        : _preSums(createPreSums(w)), _dist(1, _preSums.back()), _gen(_rd())
    {
    }

    int pickIndex()
    {
        if (_preSums.size() == 1)
            return -1;

        const int val = randomNumber();
        int left = 0;
        int right = _preSums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (_preSums[mid] == val)
                return mid - 1; // _preSums has an extra element

            if (_preSums[mid] > val) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }

        } // the loop terminates when left = right + 1
        return right;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */