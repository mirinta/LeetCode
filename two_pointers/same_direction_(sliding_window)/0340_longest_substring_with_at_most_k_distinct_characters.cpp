#include <string>
#include <unordered_map>

/**
 * Given a string s and an integer k, return the length of the longest
 * substring of s that contains at most k distinct characters.
 *
 * ! 1 <= s.length <= 5 * 10^4
 * ! 0 <= k <= 50
 */

class Solution
{
public:
    int lengthOfLongestSubstringKDistinct(std::string s, int k)
    {
        std::unordered_map<char, int> freq;
        int left = 0;
        int right = 0;
        int result = 0;
        // sliding window, elements in range [left, right)
        while (right < s.size()) {
            freq[s[right++]]++;
            while (freq.size() > k) {
                if (freq[s[left]] == 1) {
                    freq.erase(s[left]);
                } else {
                    freq[s[left]]--;
                }
                left++;
            }
            result = std::max(result, right - left);
        }
        return result;
    }
};