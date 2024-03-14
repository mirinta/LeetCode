#include <string>
#include <vector>

/**
 * You are given two strings s and p where p is a subsequence of s. You are also given a distinct
 * 0-indexed integer array removable containing a subset of indices of s (s is also 0-indexed).
 *
 * You want to choose an integer k (0 <= k <= removable.length) such that, after removing k
 * characters from s using the first k indices in removable, p is still a subsequence of s. More
 * formally, you will mark the character at s[removable[i]] for each 0 <= i < k, then remove all
 * marked characters and check if p is still a subsequence.
 *
 * Return the maximum k you can choose such that p is still a subsequence of s after the removals.
 *
 * A subsequence of a string is a new string generated from the original string with some characters
 * (can be none) deleted without changing the relative order of the remaining characters.
 *
 * ! 1 <= p.length <= s.length <= 10^5
 * ! 0 <= removable.length < s.length
 * ! 0 <= removable[i] < s.length
 * ! p is a subsequence of s.
 * ! s and p both consist of lowercase English letters.
 * ! The elements in removable are distinct.
 */

class Solution
{
public:
    int maximumRemovals(std::string s, std::string p, std::vector<int>& removable)
    {
        int min = 0;
        int max = removable.size();
        while (min < max) {
            const int k = max - (max - min) / 2;
            auto copy = s;
            for (int i = 0; i < k; ++i) {
                copy[removable[i]] = '#';
            }
            if (isValid(k, copy, p)) {
                min = k;
            } else {
                max = k - 1;
            }
        }
        return max;
    }

private:
    bool isValid(int k, const std::string& s, const std::string& p)
    {
        for (int i = 0, j = 0; i < s.size(); ++i) {
            if (s[i] == p[j]) {
                j++;
            }
            if (j == p.size())
                return true;
        }
        return false;
    }
};