/**
 * The knows API is defined as follows.
 */
bool knows(int a, int b);

/**
 * Suppose you are at a party with "n" people labeled from 0 to n - 1 and among them, there may
 * exist one celebrity. The definition of a celebrity is that all the other n - 1 people know the
 * celebrity, but the celebrity does not know any of them.
 *
 * Now you want to find out who the celebrity is or verify that there is not one. You are only
 * allowed to ask questions like: "Hi, A. Do you know B?" to get information about whether A knows
 * B. You need to find out the celebrity (or verify there is not one) by asking as few questions as
 * possible (in the asymptotic sense).
 *
 * You are given a helper function bool knows(a, b) that tells you whether a knows b. Implement a
 * function in findCelebrity(n).
 *
 * ! There will be exactly one celebrity if they are at the party.
 *
 * Return the celebrity's label if there is a celebrity at the party. If there is no celebrity,
 * return -1.
 *
 * ! If the maximum number of allowed calls to the API "knows" is 3 * n.
 * ! Could you find a solution without exceeding the maximum number of calls?
 */

class Solution
{
public:
    int findCelebrity(int n)
    {
        if (n < 2)
            return -1;

        // [set1, celebrity, set2]
        // conditions:
        // 1. !knows(celebrity, i), i in set1
        // 2. !knows(celebrity, j), j in set2
        // 3. knows(k, celebrity), k in set1 + set2
        int celebrity = 0;
        // if knows(celebrity, i), then celebrity = i
        // this makes condition 2 satisfied
        for (int i = 1; i < n; ++i) {
            if (knows(celebrity, i)) {
                celebrity = i;
            }
        }
        // check condition 1 and condition 3:
        for (int i = 0; i < n; ++i) {
            if (i < celebrity && knows(celebrity, i))
                return -1;

            if (!knows(i, celebrity))
                return -1;
        }
        return celebrity;
    }
};