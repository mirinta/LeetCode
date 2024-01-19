#include <cmath>
#include <string>

/**
 * You are given three integers start, finish, and limit. You are also given a 0-indexed string s
 * representing a positive integer.
 *
 * A positive integer x is called powerful if it ends with s (in other words, s is a suffix of x)
 * and each digit in x is at most limit.
 *
 * Return the total number of powerful integers in the range [start..finish].
 *
 * A string x is a suffix of a string y if and only if x is a substring of y that starts from some
 * index (including 0) in y and extends to the index y.length - 1. For example, 25 is a suffix of
 * 5125 whereas 512 is not.
 *
 * ! 1 <= start <= finish <= 10^15
 * ! 1 <= limit <= 9
 * ! 1 <= s.length <= floor(log10(finish)) + 1
 * ! s only consists of numeric digits which are at most limit.
 * ! s does not have leading zeros.
 */

class Solution
{
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, std::string s)
    {
        return solve(std::to_string(finish), limit, s) - solve(std::to_string(start - 1), limit, s);
    }

private:
    // total number of valid integers:
    // each integer is in the range [1,stoll(s)] and it ends with stoll(suffix)
    long long solve(const std::string& s, int limit, const std::string& suffix)
    {
        if (s.size() < suffix.size())
            return 0;

        return dfs(0, true, s, limit, suffix);
    }

    long long dfs(int i, bool isPrefixSame, const std::string& s, int limit,
                  const std::string& suffix)
    {
        // X X X X X X X i X X X X X X X
        // |<--prefix->|   |<--suffix->|
        // |<-------------s------------>
        const int n = s.size();
        const int suffixLength = suffix.size();
        if (i == n - suffixLength) {
            if (!isPrefixSame || std::stoll(s.substr(i, suffixLength)) >= std::stoll(suffix))
                return 1;

            return 0;
        }
        // case 1: different prefix, current digit and the remaining digits can be [0:limit]
        if (!isPrefixSame)
            return std::pow(1 + limit, n - i - suffixLength);

        // case 2: same prefix, current digit can be [0:min(limit, s[i]-'0)]
        long long result = 0;
        for (int j = 0; j <= std::min(s[i] - '0', limit); ++j) {
            result += dfs(i + 1, j == s[i] - '0', s, limit, suffix);
        }
        return result;
    }
};