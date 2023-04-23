#include <vector>

/**
 * You are given an integer "n" and an array of unique integers "blacklist". Design an algorithm to
 * pick a random integer in the range [0, n - 1] that is not in "blacklist". Any integer that is in
 * the mentioned range and not in "blacklist" should be equally likely to be returned.
 *
 * Optimize your algorithm such that it minimizes the number of calls to the built-in random
 * function of your language.
 *
 * Implement the "Solution" class:
 *
 * - "Solution(int n, int [] blacklist)" initializes the object with the integer "n" and the
 * blacklisted integers "blacklist".
 *
 * - "int pick()" returns a random integer in the range [0, n - 1] and not in "blacklist".
 */

class Solution
{
public:
    Solution(int n, std::vector<int>& blacklist) {}

    int pick() {}
};

/**
 * Your Solution object will be initialized and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */