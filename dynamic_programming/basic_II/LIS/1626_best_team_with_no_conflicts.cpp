#include <algorithm>
#include <vector>

/**
 * You are the manager of a basketball team. For the upcoming tournament, you want to choose the
 * team with the highest overall score. The score of the team is the sum of scores of all the
 * players in the team.
 *
 * However, the basketball team is not allowed to have conflicts. A conflict exists if a younger
 * player has a strictly higher score than an older player. A conflict does not occur between
 * players of the same age.
 *
 * Given two lists, scores and ages, where each scores[i] and ages[i] represents the score and age
 * of the ith player, respectively, return the highest overall score of all possible basketball
 * teams.
 *
 * ! 1 <= scores.length, ages.length <= 1000
 * ! scores.length == ages.length
 * ! 1 <= scores[i] <= 10^6
 * ! 1 <= ages[i] <= 1000
 */

class Solution
{
public:
    int bestTeamScore(const std::vector<int>& scores, const std::vector<int>& ages)
    {
        const int n = scores.size();
        std::vector<std::pair<int, int>> players(n); // <score, age>
        for (int i = 0; i < n; ++i) {
            players[i].first = scores[i];
            players[i].second = ages[i];
        }
        std::sort(players.begin(), players.end());
        // dp[i] = max score of teams ending at players[i]
        // base case: dp[i] = score[i]
        std::vector<int> dp(n);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = players[i].first;
            result = std::max(result, dp[i]);
        }
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                // X X j X X i
                // players are sorted by scores in non-decreasing order
                // players[i].first >= player[j].first is guaranteed
                if (players[i].second >= players[j].second) {
                    dp[i] = std::max(dp[i], players[i].first + dp[j]);
                }
            }
            result = std::max(result, dp[i]);
        }
        return result;
    }
};