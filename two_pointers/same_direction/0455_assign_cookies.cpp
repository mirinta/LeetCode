#include <algorithm>
#include <vector>

/**
 * Assume you are an awesome parent and want to give your children some cookies. But, you should
 * give each child at most one cookie.
 *
 * Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will
 * be content with; and each cookie j has a size s[j]. If s[j] >= g[i], we can assign the cookie j
 * to the child i, and the child i will be content. Your goal is to maximize the number of your
 * content children and output the maximum number.
 *
 * ! 1 <= g.length <= 3 * 10^4
 * ! 0 <= s.length <= 3 * 10^4
 * ! 1 <= g[i], s[j] <= 2^31 - 1
 */

class Solution
{
public:
    int findContentChildren(std::vector<int>& g, std::vector<int>& s)
    {
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());
        int i = 0;
        int j = 0;
        while (i < g.size() && j < s.size()) {
            if (s[j] >= g[i]) {
                i++;
            }
            j++;
        }
        return i;
    }
};