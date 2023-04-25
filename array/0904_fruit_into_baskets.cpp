#include <climits>
#include <unordered_map>
#include <vector>

/**
 * You are visiting a farm that has a single row of fruit trees arranged from left to right. The
 * trees are represented by an integer array "fruits" where "fruits[i]" is the type of fruit the
 * "i"th tree produces.
 *
 * You want to collect as much fruit as possible. However, the owner has some strict rules that you
 * must follow:
 *
 * - You only have two baskets, and each basket can only hold a single type of fruit. There is no
 * limit on the amount of fruit each basket can hold.
 *
 * - Starting from any tree of your choice, you must pick exactly one fruit from every tree
 * (including the start tree) while moving to the right. The picked fruits must fit in one of your
 * baskets.
 *
 * - Once you reach a tree with fruit that cannot fit in your baskets, you must stop.
 *
 * Given the integer array "fruits", return the "maximum" number of fruits you can pick.
 */

class Solution
{
public:
    int totalFruit(const std::vector<int>& fruits)
    {
        const auto size = fruits.size();
        if (size <= 2)
            return size;

        std::unordered_map<int, int> baskets;
        int left = 0;
        int right = 0;
        for (; right < size; ++right) {
            baskets[fruits[right]]++;
            if (baskets.size() > 2) {
                const auto type = fruits[left++];
                if (--baskets[type] == 0) {
                    baskets.erase(type);
                }
            }
        }
        return right - left;
        // const auto size = fruits.size();
        // if (size <= 2)
        //     return size;

        // std::unordered_map<int, int> freq;
        // int left = 0;
        // int right = 0;
        // int result = INT_MIN;
        // while (right < size) {
        // expand window
        //     const auto typeRight = fruits[right];
        //     if (freq.count(typeRight) || freq.size() < 2) {
        //         freq[typeRight]++;
        //         right++;
        //         result = std::max(result, right - left);
        //         continue;
        //     }
        // shrink window
        //     while (freq.size() == 2) {
        //         const auto typeLeft = fruits[left++];
        //         if (--freq[typeLeft] == 0) {
        //             freq.erase(typeLeft);
        //         }
        //     }
        // }
        // return result == INT_MIN ? 0 : result;
    }
};