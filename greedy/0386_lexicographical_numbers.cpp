#include <vector>

/**
 * Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.
 *
 * You must write an algorithm that runs in O(n) time and uses O(1) extra space.
 *
 * ! 1 <= n <= 5 * 10^4
 */

class Solution
{
public:
    std::vector<int> lexicalOrder(int n)
    {
        std::vector<int> result{1};
        int i = 1;
        while (result.size() < n) {
            if (i * 10 <= n) {
                i *= 10;
            } else {
                while (i + 1 > n || i % 10 == 9) {
                    i /= 10;
                }
                i++;
            }
            result.push_back(i);
        }
        return result;
    }
};