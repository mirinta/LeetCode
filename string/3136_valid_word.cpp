#include <string>

/**
 * A word is considered valid if:
 *
 * - It contains a minimum of 3 characters.
 *
 * - It consists of the digits 0-9, and the uppercase and lowercase English letters. (Not necessary
 * to have all of them.)
 *
 * - It includes at least one vowel.
 *
 * - It includes at least one consonant. You are given a string word.
 *
 * Return true if word is valid, otherwise, return false.
 *
 * Notes:
 *
 * - 'a', 'e', 'i', 'o', 'u', and their uppercases are vowels.
 *
 * - A consonant is an English letter that is not a vowel.
 *
 * ! 1 <= word.length <= 20
 * ! word consists of English uppercase and lowercase letters, digits, '@', '#', and '$'.
 */

class Solution
{
public:
    bool isValid(std::string word)
    {
        if (word.size() < 3)
            return false;

        bool vowel = false;
        bool consonant = false;
        for (const auto& c : word) {
            if (!std::isalnum(c))
                return false;

            if (std::isdigit(c))
                continue;

            if (isVowel(std::tolower(c))) {
                vowel = true;
            } else {
                consonant = true;
            }
        }
        return vowel && consonant;
    }

private:
    bool isVowel(char c) { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }
};