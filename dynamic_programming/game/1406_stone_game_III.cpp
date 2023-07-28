#include <string>
#include <vector>

/**
 * Alice and Bob continue their games with piles of stones. There are several stones arranged in a
 * row, and each stone has an associated value which is an integer given in the array "stoneValue".
 *
 * Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take
 * 1, 2, or 3 stones from the first remaining stones in the row.
 *
 * The score of each player is the sum of the values of the stones taken. The score of each player
 * is 0 initially.
 *
 * The objective of the game is to end with the highest score, and the winner is the player with the
 * highest score and there could be a tie. The game continues until all the stones have been taken.
 *
 * Assume Alice and Bob play optimally.
 *
 * Return "Alice" if Alice win, "Bob" if Bob will win, or "Tie" if they will end the game with the
 * same score.
 *
 * ! -1000 <= stoneValue[i] <= 1000
 */

class Solution
{
public:
    std::string stoneGameIII(const std::vector<int>& stoneValue)
    {
        const auto n = stoneValue.size();
        if (n == 0)
            return {};

        // approach 2: iterative DP
        std::vector<int> suffixSum(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + stoneValue[i];
        }
        // dp[i] = the max score the player can get when the game starts with stones[i:n)
        std::vector<int> dp(n + 1, INT_MIN); // stoneValue[i] may be negative
        dp[n] = 0;                           // no stone to take
        for (int i = n - 1; i >= 0; --i) {
            int score = 0;
            for (int choice = 1; choice <= 3; ++choice) {
                if (i + choice - 1 >= n)
                    break;

                score += stoneValue[i + choice - 1];
                dp[i] = std::max(dp[i], score + suffixSum[i + choice] - dp[i + choice]);
            }
        }
        const int diff = 2 * dp[0] - suffixSum[0];
        if (diff == 0)
            return "Tie";

        return diff > 0 ? "Alice" : "Bob";
    }

private:
    // approach 1: similar to LC 1140
    // - In LC 1140, we computes the highest value that Alice can take
    // - Since both players are optimal, Alice's best strategy is established based on Bob's best
    // strategy
    // - Because this is a zero-sum game, we know that max_score_alice + max_score_bob = total_score
    // - Thus, we can compare max_score_alice and max_score_bob to find out the winner
    std::string stoneGameIII_v1(const std::vector<int>& stoneValue)
    {
        const auto n = stoneValue.size();
        if (n == 0)
            return {};

        std::vector<int> suffixSum(n + 1, 0);
        int totalScore = 0;
        for (int i = n - 1; i >= 0; --i) {
            suffixSum[i] = stoneValue[i] + suffixSum[i + 1];
            totalScore += stoneValue[i];
        }
        std::vector<int> memo(n, INT_MIN); // stoneValue[i] may be negative value
        // aliceMaxScore = dp(0, memo, suffixSum, stoneValue)
        // bobMaxScore = totalScore - aliceMaxScore
        // difference between aliceMaxScore and bobMaxScore = 2*aliceMaxScore - total_score
        const auto diff = 2 * dp(0, memo, suffixSum, stoneValue) - totalScore;
        if (diff == 0)
            return "Tie";

        return diff > 0 ? "Alice" : "Bob";
    }

    int dp(int pos, std::vector<int>& memo, const std::vector<int>& suffixSum,
           const std::vector<int>& stoneValue)
    {
        if (pos == stoneValue.size())
            return 0;

        if (memo[pos] != INT_MIN)
            return memo[pos];

        int score = 0;
        // only 3 choices: 1, 2, or 3
        for (int choice = 1; choice <= 3; ++choice) {
            if (pos + choice - 1 >= stoneValue.size())
                break;

            score += stoneValue[pos + choice - 1];
            const int opponent = dp(pos + choice, memo, suffixSum, stoneValue);
            memo[pos] = std::max(memo[pos], score + suffixSum[pos + choice] - opponent);
        }
        return memo[pos];
    }
};