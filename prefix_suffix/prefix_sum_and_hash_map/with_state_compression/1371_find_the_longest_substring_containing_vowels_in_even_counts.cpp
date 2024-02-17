#include <string>
#include <unordered_map>

/**
 * Given the string s, return the size of the longest substring containing each vowel an even number
 * of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.
 *
 * ! 1 <= s.length <= 5 x 10^5
 * ! s contains only lowercase English letters.
 */

class Solution
{
public:
    int findTheLongestSubstring(std::string s)
    {
        // A[i] = num of a's in s[0:i]
        // E[i] = num of e's in s[0:i]
        // I[i] = num of i's in s[0:i]
        // O[i] = num of o's in s[0:i]
        // U[i] = num of u's in s[0:i]
        // if s[j+1:i] is a valid substring, then
        // (A[i]-A[j])%2=0, A[i] is even and A[j] is even, A[i] is odd and A[j] is odd
        // (E[i]-E[j])%2=0, E[i] is even and E[j] is even, E[i] is odd and E[j] is odd
        // (I[i]-I[j])%2=0, I[i] is even and I[j] is even, I[i] is odd and I[j] is odd
        // (O[i]-O[j])%2=0, O[i] is even and O[j] is even, O[i] is odd and O[j] is odd
        // (U[i]-U[j])%2=0, U[i] is even and U[j] is even, U[i] is odd and U[j] is odd
        // compress these states into 5 bits,
        //  a  e  i  o  u
        // x0 x1 x2 x3 x4
        // xi = 0 if num of the vowel is even, 1 if num of the vowel is odd
        const int n = s.size();
        std::unordered_map<int, int> map; // state to index
        map[0] = -1;
        int state = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            state ^= getState(s[i]);
            if (map.count(state)) {
                result = std::max(result, i - map[state]);
            } else {
                map[state] = i;
            }
        }
        return result;
    }

private:
    int getState(char c)
    {
        switch (c) {
        case 'a':
            return 1 << 4;
        case 'e':
            return 1 << 3;
        case 'i':
            return 1 << 2;
        case 'o':
            return 1 << 1;
        case 'u':
            return 1;
        default:
            break;
        }
        return 0;
    }
};