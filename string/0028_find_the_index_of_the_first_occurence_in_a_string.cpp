#include <string>

/**
 * Given two strings "needle" and "haystack", return the index of the first occurrence of "needle"
 * in "haystack", or "-1" if "needle" if not part of "haystack".
 */

class Solution
{
public:
    int strStr(const std::string& haystack, const std::string& needle)
    {
        if (haystack.empty() || needle.empty() || needle.size() > haystack.size())
            return -1;

        // time complexity: O(mn)
        const auto searchLength = needle.size();
        for (size_t i = 0; i <= haystack.size() - searchLength; ++i) {
            if (haystack.substr(i, searchLength) == needle)
                return i;
        }
        return -1;
    }
};