#include <algorithm>
#include <vector>

/**
 * Given a wooden stick of length n units. The stick is labelled from 0 to n. For example, a stick
 * of length 6 is labelled as follows:
 *
 * 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7
 *
 * Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.
 *
 * You can change the order of the cuts as you wish.
 *
 * The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of
 * all cuts. When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their
 * lengths is the length of the stick before the cut). Please refer to the first example for a
 * better explanation.
 *
 * ! 2 <= n <= 10^6
 * ! 1 <= cuts.length <= min(n - 1, 100)
 * ! 1 <= cuts[i] <= n - 1
 * ! All the integers in cuts array are distinct.
 */

class Solution
{
public:
    int minCost(int n, std::vector<int>& cuts)
    {
        // dp[i][j] = min cost of cutting stick[I,J], where I = cuts[i] and J = cuts[j]
        // 0 ... I .......... K .......... J ... n
        //       |<-dp[i][k]->|<-dp[k][j]->|
        //       |<--------dp[i][j]------->|
        // length = J - I
        // - if length >= 3, we can choose a cutting position K = cuts[k],
        // where K is in the range [I+1,J-1], then cost = J - I + dp[i][k] + dp[k][j]
        // - if length = 2, cost = 0, because there's no possible cutting position in stick[I,J]
        // - if length < 2, cost = INT_MAX, because stick[I,J] is invalid
        cuts.push_back(0);
        cuts.push_back(n);
        std::sort(cuts.begin(), cuts.end());
        std::vector<std::vector<int>> dp(cuts.size(), std::vector<int>(cuts.size(), INT_MAX));
        for (int i = 0; i < cuts.size() - 1; ++i) {
            dp[i][i + 1] = 0;
        }
        for (int i = cuts.size() - 3; i >= 0; --i) {
            for (int j = i + 2; j < cuts.size(); ++j) {
                for (int k = i + 1; k <= j - 1; ++k) {
                    dp[i][j] = std::min(dp[i][j], cuts[j] - cuts[i] + dp[i][k] + dp[k][j]);
                }
            }
        }
        return dp[0][cuts.size() - 1];
    }
};
