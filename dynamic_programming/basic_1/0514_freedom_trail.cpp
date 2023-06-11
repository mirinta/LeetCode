#include <string>
#include <unordered_map>
#include <vector>

/**
 * In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial
 * called the "Freedom Trail Ring" and use the dial to spell a specific keyword to open the door.
 *
 * Given a string "ring" that represents the code engraved on the outer ring and another string
 * "key" that represents the keyword that needs to be spelled, return the minimum number of steps to
 * spell all the characters in the keyword.
 *
 * Initially, the first character of the ring is aligned at the "12:00" direction. You should spell
 * all the characters in "key" one by one by rotating "ring" clockwise or anticlockwise to make each
 * character of the string key aligned at the "12:00" direction and then by pressing the center
 * button.
 *
 * At the stage of rotating the ring to spell the key character "key[i]":
 *
 * You can rotate the ring clockwise or anticlockwise by one place, which counts as one step. The
 * final purpose of the rotation is to align one of "ring"'s characters at the "12:00" direction,
 * where this character must equal "key[i]".
 *
 * If the character "key[i]" has been aligned at the "12:00" direction, press the center button to
 * spell, which also counts as one step. After the pressing, you could begin to spell the next
 * character in the key (next stage). Otherwise, you have finished all the spelling.
 *
 * ! It is guaranteed that key could always be spelled by rotating ring.
 */

class Solution
{
public:
    int findRotateSteps(std::string ring, std::string key)
    {
        const int m = ring.size();
        const int n = key.size();
        memo = std::vector<std::vector<int>>(m, std::vector<int>(n, -1));
        for (int i = 0; i < m; ++i) {
            map[ring[i]].push_back(i);
        }
        return dp(0, 0, ring, key);
    }

private:
    std::vector<std::vector<int>> memo;
    std::unordered_map<char, std::vector<int>> map;
    // min steps to spell key[j:] while ring[i] is at 12:00
    int dp(int i, int j, const std::string& ring, std::string& key)
    {
        if (j == key.size())
            return 0;

        if (memo[i][j] != -1)
            return memo[i][j];

        const int m = ring.size();
        // key[j] is the target character
        int steps = INT_MAX;
        for (const auto& k : map[key[j]]) {
            auto dist = std::abs(i - k);
            dist = std::min(dist, m - dist);
            // set ring[k] at 12:00, and the new target character becomes key[j+1]
            steps = std::min(
                steps, 1 + dist + dp(k, j + 1, ring, key)); // additional +1 means pushing button
        }
        memo[i][j] = steps;
        return steps;
    }
};