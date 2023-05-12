#include <vector>

/**
 * You are given a 0-indexed 2D integer array "questions" where "questions[i] = [points_i,
 * brainpower_i]".
 *
 * The array describes the questions of an exam, where you have to process the questions in order
 * (i.e., starting from question 0) and make a decision whether to solve or skip each question.
 * Solving question i will earn you points_i points but you will be unable to solve each of the next
 * brainpower_i questions. If you skip question i, you get to make the decision on the next
 * question.
 *
 * Return the maximum points you can earn for the exam.
 *
 * Example:
 * Input: questions = [[3, 2], [4, 3], [4, 4], [2, 5]]
 * Output: 5
 * Explanation: The maximum points can be earned by solving question 0 and 3.
 * - Solve question 0: Earn 3 points, will be unable to solve the next 2 questions
 * - Unable to solve questions 1 and 2
 * - Solve question 3: Earn 2 points
 * Total points earned: 3 + 2 = 5. There is no other way to earn 5 or more points.
 *
 * Example:
 * Input: questions = [[1, 1], [2, 2], [3, 3], [4, 4], [5, 5]]
 * Output: 7
 * Explanation: The maximum points can be earned by solving questions 1 and 4.
 * - Skip question 0
 * - Solve question 1: Earn 2 points, will be unable to solve the next 2 questions
 * - Unable to solve questions 2 and 3
 * - Solve question 4: Earn 5 points
 * Total points earned: 2 + 5 = 7. There is no other way to earn 7 or more points.
 */

class Solution
{
public:
    long long mostPoints(std::vector<std::vector<int>>& questions)
    {
        const auto n = questions.size();
        if (n < 1)
            return 0;

        // dp[i] = maximum points we can get by processing the questions [i, n - 1]
        std::vector<long long> dp(n);
        dp[n - 1] = questions[n - 1][0];
        for (long long i = n - 2; i >= 0; --i) {
            // case 1: skip the i-th problem, dp[i] = dp[i + 1]
            // case 2: solve the i-th problem, dp[i] = points[i] + dp[j]
            // - j is the index of next solvable question after the i-th question
            // - j = i + brainpower[i] + 1
            // - if j >= n, there is no solvable question after solving the i-th question which
            // means dp[j] = 0
            const auto j = i + questions[i][1] + 1;
            dp[i] = std::max(dp[i + 1], j < n ? dp[j] + questions[i][0] : questions[i][0]);
        }
        return dp[0];
    }
};