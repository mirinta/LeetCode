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
 *
 * INTUITION:
 * Let w = [1, 3, 2, 1]:
 *                       0   1  2 3 <- indices
 * draw line segments: |*|***|**|*|
 * prefix sums of w:     1   3  6 7 <- accumulative sums
 *
 */

class Solutoin
{
public:
    Solutoin(std::vector<int>& m) {}

    int pickIndex() {}
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */