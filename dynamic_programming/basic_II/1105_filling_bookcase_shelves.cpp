#include <vector>

/**
 * You are given an array books where books[i] = [thicknessi, heighti] indicates the thickness and
 * height of the ith book. You are also given an integer shelfWidth.
 *
 * We want to place these books in order onto bookcase shelves that have a total width shelfWidth.
 *
 * We choose some of the books to place on this shelf such that the sum of their thickness is less
 * than or equal to shelfWidth, then build another level of the shelf of the bookcase so that the
 * total height of the bookcase has increased by the maximum height of the books we just put down.
 * We repeat this process until there are no more books to place.
 *
 * Note that at each step of the above process, the order of the books we place is the same order as
 * the given sequence of books.
 *
 * - For example, if we have an ordered list of 5 books, we might place the first and second book
 * onto the first shelf, the third book on the second shelf, and the fourth and fifth book on the
 * last shelf.
 *
 * Return the minimum possible height that the total bookshelf can be after placing shelves in this
 * manner.
 *
 * ! 1 <= books.length <= 1000
 * ! 1 <= thickness_i <= shelfWidth <= 1000
 * ! 1 <= height_i <= 1000
 */

class Solution
{
public:
    int minHeightShelves(std::vector<std::vector<int>>& books, int shelfWidth)
    {
        const int n = books.size();
        // dp[i] = minHeightShelves of the first i books, width of each shelf <= shelfWidth
        std::vector<int> dp(n + 1, INT_MAX);
        // base case:
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            // X X j X X X X X X i
            //     | same shelf  |
            // the books must be placed in order
            // for the ith book, suppose we can place
            // jth, j+1th, ... ith book in the same shelf,
            // where sum(width(j), width(j+1), ..., width(i)) <= shelfWidth
            // then, height of this shelf is max(height(j), height(j+1), ..., height(i))
            int width = 0;
            int maxHeight = 0;
            for (int j = i; j >= 1; --j) {
                width += books[j - 1][0];
                if (width > shelfWidth)
                    break;

                maxHeight = std::max(maxHeight, books[j - 1][1]);
                dp[i] = std::min(dp[i], dp[j - 1] + maxHeight);
            }
        }
        return dp[n];
    }
};