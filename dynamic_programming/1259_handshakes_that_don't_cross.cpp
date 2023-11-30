#include <vector>

/**
 * You are given an even number of people numPeople that stand around a circle and each person
 * shakes hands with someone else so that there are numPeople / 2 handshakes total.
 *
 * Return the number of ways these handshakes could occur such that none of the handshakes cross.
 *
 * Since the answer could be very large, return it modulo 10^9 + 7.
 *
 * ! 2 <= numPeople <= 1000
 * ! numPeople is even.
 */

class Solution
{
public:
    int numberOfWays(int numPeople)
    {
        constexpr int kMod = 1e9 + 7;
        // dp[i] = num of ways of handshakes between i people
        // assume there are i people
        // - let person 1 shake hands with peron x, then the circle is divided into two parts
        // - the left part contains person[x+1:i], num of people = x - 2
        // - the right part contains person[2:x-1], num of people = i - x
        // - num of ways = dp[x-2] * dp[i-x]
        //       1
        //   i   |   2
        //  ...  |  ...
        //  x+1  |  x-1
        //       x
        std::vector<long long> dp(numPeople + 1, 0);
        dp[0] = 1;
        dp[2] = 1;
        for (int i = 4; i <= numPeople; i += 2) {
            // j is the num of people in the right part
            for (int j = 0; j <= i - 2; j += 2) {
                dp[i] = (dp[i] + dp[j] * dp[i - j - 2]) % kMod;
            }
        }
        return dp[numPeople];
    }
};