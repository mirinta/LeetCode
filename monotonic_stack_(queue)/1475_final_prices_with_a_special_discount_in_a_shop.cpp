#include <stack>
#include <vector>

/**
 * You are given an integer array prices where prices[i] is the price of the ith item in a shop.
 *
 * There is a special discount for items in the shop. If you buy the ith item, then you will receive
 * a discount equivalent to prices[j] where j is the minimum index such that j > i and prices[j] <=
 * prices[i]. Otherwise, you will not receive any discount at all.
 *
 * Return an integer array answer where answer[i] is the final price you will pay for the ith item
 * of the shop, considering the special discount.
 *
 * ! 1 <= prices.length <= 500
 * ! 1 <= prices[i] <= 1000
 */

class Solution
{
public:
    std::vector<int> finalPrices(std::vector<int>& prices) { return approach2(prices); }

private:
    // monotonic stack, time O(N), space O(N)
    std::vector<int> approach2(const std::vector<int>& prices)
    {
        // finding the next smaller or equal element
        const int n = prices.size();
        std::vector<int> result(n);
        std::stack<int> stack;
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && prices[i] < prices[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? prices[i] : prices[i] - prices[stack.top()];
            stack.push(i);
        }
        return result;
    }

    // brute-force, time O(N^2), space O(N)
    std::vector<int> approach1(const std::vector<int>& prices)
    {
        const int n = prices.size();
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            int discount = 0;
            for (int j = i + 1; j < n; ++j) {
                if (prices[j] <= prices[i]) {
                    discount = prices[j];
                    break;
                }
            }
            result[i] = prices[i] - discount;
        }
        return result;
    }
};