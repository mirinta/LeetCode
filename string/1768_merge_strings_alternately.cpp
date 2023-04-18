#include <string>

/**
 * You are given two strings "word1" and "word2". Merge the strings by adding letters in alternating
 * order, starting with "word1". If a string is longer than the other, append the additional letters
 * onto the end of the merged string.
 *
 * Return the merged string.
 */

class Solution
{
public:
    std::string mergeAlternately(const std::string& word1, const std::string& word2)
    {
        if (word1.empty())
            return word2;

        if (word2.empty())
            return word1;

        const size_t length1 = word1.size();
        const size_t length2 = word2.size();
        size_t iter1 = 0;
        size_t iter2 = 0;
        std::string result{};
        while (iter1 < length1 || iter2 < length2) {
            if (iter1 < length1) {
                result.push_back(word1[iter1++]);
            }
            if (iter2 < length2) {
                result.push_back(word2[iter2++]);
            }
        }
        return result;
    }
};