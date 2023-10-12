#include <string>

/**
 * Given a positive integer n, return the punishment number of n.
 *
 * The punishment number of n is defined as the sum of the squares of all integers i such that:
 *
 * - 1 <= i <= n
 *
 * - The decimal representation of i * i can be partitioned into contiguous substrings such that the
 * sum of the integer values of these substrings equals i.
 *
 * ! 1 <= n <= 1000
 */

class Solution
{
public:
    int punishmentNumber(int n)
    {
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            int sum = 0;
            const int square = i * i;
            if (backtrack(sum, 0, i, std::to_string(square))) {
                result += square;
            }
        }
        return result;
    }

private:
    // check target*target can be partitioned into contiguous substrings
    // s.t. that the sum of the integer values of these substrings equals "target"
    bool backtrack(int& sum, int start, int target, const std::string& s)
    {
        if (start == s.size())
            return sum == target;

        // substring s[start:end]
        for (int end = start; end < s.size(); ++end) {
            int val = 0;
            for (int i = start; i <= end; ++i) {
                val = val * 10 + (s[i] - '0');
            }
            sum += val;
            if (backtrack(sum, end + 1, target, s))
                return true;

            sum -= val;
        }
        return false;
    }
};