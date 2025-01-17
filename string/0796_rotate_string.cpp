#include <string>

/**
 * Given two strings s and goal, return true if and only if s can become goal after some number of
 * shifts on s.
 *
 * A shift on s consists of moving the leftmost character of s to the rightmost position.
 *
 * - For example, if s = "abcde", then it will be "bcdea" after one shift.
 *
 * ! 1 <= s.length, goal.length <= 100
 * ! s and goal consist of lowercase English letters.
 */

class Solution
{
public:
    bool rotateString(std::string s, std::string goal)
    {
        if (s.size() != goal.size())
            return false;

        s += s;
        return s.find(goal) != std::string::npos;
    }
};