#include <string>

/**
 * Given a string "s" and an integer "k", return the maximum number of vowel letters in any
 * substring of "s" with length "k".
 *
 * Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
 */

class Solution
{
public:
    int maxVowels(const std::string& s, int k)
    {
        if (s.size() < k || k < 1)
            return 0;

        int result = INT_MIN;
        int count = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            if (isVowel(s[i])) {
                count++;
            }
            if (i >= k && isVowel(s[i - k])) {
                count--;
            }
            result = std::max(result, count);
        }
        return result;
    }

private:
    inline bool isVowel(char c)
    {
        switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            break;
        }
        return false;
    }
};