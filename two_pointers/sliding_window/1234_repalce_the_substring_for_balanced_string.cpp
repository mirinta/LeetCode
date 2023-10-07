#include <algorithm>
#include <string>
#include <unordered_map>

/**
 * You are given a string s of length n containing only four kinds of characters: 'Q', 'W', 'E', and
 * 'R'.
 *
 * A string is said to be balanced if each of its characters appears n / 4 times where n is the
 * length of the string.
 *
 * Return the minimum length of the substring that can be replaced with any other string of the same
 * length to make s balanced. If s is already balanced, return 0.
 *
 * ! n == s.length
 * ! 4 <= n <= 10^5
 * ! n is a multiple of 4.
 * ! s contains only 'Q', 'W', 'E', and 'R'.
 */

class Solution
{
public:
    int balancedString(std::string s)
    {
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        const int n = s.size();
        const int targetCount = n / 4;
        auto equalToTargetCount = [&targetCount](const auto& pair) {
            return pair.second == targetCount;
        };
        if (std::all_of(map.begin(), map.end(), equalToTargetCount))
            return 0;

        // X X X X X X X ...
        // |<--window->|
        // if the frequency of each character outside the window <= n/4
        // then we can make the entire string balanced
        auto lessThanOrEqualToTargetCount = [&targetCount](const auto& pair) {
            return pair.second <= targetCount;
        };
        int result = INT_MAX;
        for (int left = 0, right = 0; right < n; ++right) {
            map[s[right]]--;
            while (std::all_of(map.begin(), map.end(), lessThanOrEqualToTargetCount)) {
                result = std::min(result, right - left + 1);
                map[s[left]]++;
                left++;
            }
        }
        return result;
    }
};