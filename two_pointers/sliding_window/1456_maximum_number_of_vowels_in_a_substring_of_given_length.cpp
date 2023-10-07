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
    int maxVowels(std::string s, int k)
    {
        int count = 0;
        for (int i = 0; i < k; ++i) {
            if (isVowel(s[i])) {
                count++;
            }
        }
        int result = count;
        for (int i = k; i < s.size(); ++i) {
            count -= isVowel(s[i - k]);
            count += isVowel(s[i]);
            result = std::max(result, count);
        }
        return result;
    }

private:
    bool isVowel(char c)
    {
        // only lowercase English letters
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};