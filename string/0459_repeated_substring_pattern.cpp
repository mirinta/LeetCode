#include <string>

/**
 * Given a string "s", check if it can be constructed by taking a substring of it and appending
 * multiple copies of teh substring together.
 */

class Solution
{
public:
    bool repeatedSubstringPattern(const std::string& s)
    {
        if (s.empty())
            return false;

        const auto concat = s + s;
        const auto sub = concat.substr(1, concat.size() - 2);
        return sub.find(s) != std::string::npos;
    }
};