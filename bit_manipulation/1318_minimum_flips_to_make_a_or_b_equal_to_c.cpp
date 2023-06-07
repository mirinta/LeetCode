/**
 * Given 3 positive numbers "a", "b", and "c". Return the minimum flips required in some bits of "a"
 * and "b" to make ("a" OR "b" == "c").
 *
 * Flip operation consists of change any single bit 1 to 0 or change the bit 0 to 1 in their binary
 * representations.
 *
 * ! 1 <= a <= 10^9
 * ! 1 <= b <= 10^9
 * ! 1 <= c <= 10^9
 */

class Solution
{
public:
    int minFlips(int a, int b, int c)
    {
        if ((a | b) == c)
            return 0;

        // a, b, and c are >= 1
        // - right-shift on negative numbers will fill the vacated positions with 1
        int result = 0;
        while (a > 0 || b > 0 || c > 0) {
            int lastOfA = a & 1;
            int lastOfB = b & 1;
            int lastOfC = c & 1;
            if ((lastOfA | lastOfB) != lastOfC) {
                if (lastOfC) {
                    // lastOfC = 1, both lastOfA and lastOfB are 0, flip one of them
                    result += 1;
                } else if (lastOfA && lastOfB) {
                    // lastOfC = 0, both lastOfA and lastOfB are 1, flip both of them
                    result += 2;
                } else {
                    // lastOfC = 0, either lastOfA or lastOfB is 1, flip the one that is equal to 1
                    result += 1;
                }
            }
            a = a >> 1;
            b = b >> 1;
            c = c >> 1;
        }
        return result;
    }
};