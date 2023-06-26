#include <algorithm>
#include <stack>
#include <string>
#include <vector>

/**
 * There are n 1-indexed robots, each having a position on a line, health, and movement direction.
 *
 * You are given 0-indexed integer arrays positions, healths, and a string directions (directions[i]
 * is either 'L' for left or 'R' for right). All integers in positions are unique.
 *
 * All robots start moving on the line simultaneously at the same speed in their given directions.
 * If two robots ever share the same position while moving, they will collide.
 *
 * If two robots collide, the robot with lower health is removed from the line, and the health of
 * the other robot decreases by one. The surviving robot continues in the same direction it was
 * going. If both robots have the same health, they are both removed from the line.
 *
 * Your task is to determine the health of the robots that survive the collisions, in the same order
 * that the robots were given, i.e. final heath of robot 1 (if survived), final health of robot 2
 * (if survived), and so on. If there are no survivors, return an empty array.
 *
 * Return an array containing the health of the remaining robots (in the order they were given in
 * the input), after no further collisions can occur.
 *
 * Note: The positions may be unsorted.
 *
 * ! 1 <= positions.length == healths.length == directions.length == n <= 10^5
 * ! 1 <= positions[i], healths[i] <= 10^9
 * ! directions[i] == 'L' or directions[i] == 'R'
 * ! All values in positions are distinct
 */

class Solution
{
public:
    std::vector<int> survivedRobotsHealths(std::vector<int>& positions, std::vector<int>& healths,
                                           std::string directions)
    {
        if (positions.size() < 2)
            return healths;

        std::vector<std::pair<int, int>> pairs;
        for (int i = 0; i < positions.size(); ++i) {
            pairs.push_back({positions[i], i});
        }
        std::sort(pairs.begin(), pairs.end());
        std::stack<int> robotsGoRight;
        for (const auto& [pos, i] : pairs) {
            if (directions[i] == 'R') {
                robotsGoRight.push(i);
                continue;
            }
            while (healths[i] && !robotsGoRight.empty()) {
                const int j = robotsGoRight.top();
                robotsGoRight.pop();
                if (healths[j] == healths[i]) {
                    healths[i] = 0;
                    healths[j] = 0;
                } else if (healths[i] > healths[j]) {
                    healths[i]--;
                    healths[j] = 0;
                } else {
                    healths[i] = 0;
                    healths[j]--;
                    if (healths[j] > 0) {
                        robotsGoRight.push(j);
                    }
                }
            }
        }
        std::vector<int> result;
        for (const auto& health : healths) {
            if (health > 0) {
                result.push_back(health);
            }
        }
        return result;
    }
};