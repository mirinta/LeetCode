#include <vector>

/**
 * Your music player contains n different songs. You want to listen to goal songs (not necessarily
 * different) during your trip. To avoid boredom, you will create a playlist so that:
 *
 * - Every song is played at least once.
 *
 * - A song can only be played again only if k other songs have been played.
 *
 * Given n, goal, and k, return the number of possible playlists that you can create. Since the
 * answer can be very large, return it modulo 10^9 + 7.
 *
 * ! 0 <= k < n <= goal <= 100
 */

class Solution
{
public:
    int numMusicPlaylists(int n, int goal, int k)
    {
        constexpr int kMod = 1e9 + 7;
        // dp[i][j] = num of ways to make a playlist with length i and j unique songs
        std::vector<std::vector<long>> dp(goal + 1, std::vector<long>(n + 1, 0));
        dp[0][0] = 1;
        // two cases of choosing the ith song of the playlist:
        // - case1, choose a song that is already in the playlist, i.e. an old song
        // - case2, choose a song that is not in the playlist, i.e., a new song
        for (int i = 1; i <= goal; ++i) {
            for (int j = 1; j <= n; ++j) {
                // case1:
                // - suppose we have a playlist with length 4 using 4 unique songs,
                //   we want to choose the 5th song from the 4 old songs
                // - 1,2,3,4,?
                // - if k=0, we have 4 choices for ?, i.e., {1,2,3,4}
                // - if k=1, we have 3 choices for ?, i.e., {1,2,3}
                // - if k=2, we have 2 choices for ?, i.e., {1,2}
                // - if k=3, we have 1 choice for ?, i.e., {1}
                // - if k>=4, we have no choice for ?
                // - thus, we can choose an old song only if j>k, and there are j-k choices
                if (j > k) {
                    // X X X X X X i-1 i
                    // | j old songs |
                    dp[i][j] = (dp[i][j] + dp[i - 1][j] * (j - k)) % kMod;
                }
                // case 2:
                if (n - j + 1 > 0) {
                    // X X X X X X j-1 j X X X X X X X n
                    // |j-1 old songs| |n-j+1 new songs|
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1] * (n - j + 1)) % kMod;
                }
            }
        }
        return dp[goal][n];
    }
};