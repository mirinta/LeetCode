#include <string>
#include <unordered_map>
#include <vector>

/**
 * We can shift a string by shifting each of its letters to its successive letter.
 *
 * - For example, "abc" can be shifted to be "bcd".
 *
 * We can keep shifting the string to form a sequence.
 *
 * - For example, we can keep shifting "abc" to form the sequence: "abc" -> "bcd" -> ... -> "xyz".
 *
 * Given an array of strings strings, group all strings[i] that belong to the same shifting
 * sequence. You may return the answer in any order.
 *
 * ! 1 <= strings.length <= 200
 * ! 1 <= strings[i].length <= 50
 * ! strings[i] consists of lowercase English letters.
 */

class Solution
{
public:
    std::vector<std::vector<std::string>> groupStrings(std::vector<std::string>& strings)
    {
        // shift "acp"
        // - a to b
        // - c to d
        // - q to q
        // thus, "bdq"
        std::unordered_map<std::string, std::vector<std::string>> map;
        for (const auto& s : strings) {
            map[encode(s)].push_back(s);
        }
        std::vector<std::vector<std::string>> result;
        result.reserve(map.size());
        for (const auto& [key, group] : map) {
            result.push_back(group);
        }
        return result;
    }

private:
    int shiftTimes(const std::string& s)
    {
        // how many times to shift s[0] to 'a'
        // e.g. 25 times to shift 'b' to 'a'
        return 26 - (s[0] - 'a');
    }

    std::string encode(const std::string& s)
    {
        // shift s such that s[0] = 'a'
        const int times = shiftTimes(s);
        std::string result(s);
        for (auto& c : result) {
            c = (c - 'a' + times) % 26 + 'a';
        }
        return result;
    }
};