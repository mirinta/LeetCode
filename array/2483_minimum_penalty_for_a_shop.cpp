#include <string>
#include <vector>

/**
 * You are given the customer visit log of a shop represented by a 0-indexed string customers
 * consisting only of characters 'N' and 'Y':
 *
 * - if the ith character is 'Y', it means that customers come at the ith hour
 *
 * - whereas 'N' indicates that no customers come at the ith hour.
 *
 * If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated as follows:
 *
 * - For every hour when the shop is open and no customers come, the penalty increases by 1.
 *
 * - For every hour when the shop is closed and customers come, the penalty increases by 1.
 *
 * Return the earliest hour at which the shop must be closed to incur a minimum penalty.
 *
 * Note that if a shop closes at the jth hour, it means the shop is closed at the hour j.
 *
 * ! 1 <= customers.length <= 10^5
 * ! customers consists only of characters 'Y' and 'N'.
 */

class Solution
{
public:
    int bestClosingTime(std::string customers) { return approach2(customers); }

private:
    // One-pass, time O(N), space O(1)
    int approach2(const std::string& customers)
    {
        const int n = customers.size();
        int result = 0;
        int penalty = 0;
        int minPenalty = 0;
        for (int i = 0; i < n; ++i) {
            if (customers[i] == 'Y') {
                penalty--;
            } else {
                penalty++;
            }
            if (penalty < minPenalty) {
                result = i + 1;
                minPenalty = penalty;
            }
        }
        return result;
    }

    // Three-pass, time O(N), space O(N)
    int approach1(const std::string& customers)
    {
        // X X X X X X j X X X X X X
        // |<-OPEN-->| |<--CLOSED->|
        const int n = customers.size();
        std::vector<int> prefix(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            if (customers[i - 1] == 'N') {
                prefix[i] = prefix[i - 1] + 1;
            } else {
                prefix[i] = prefix[i - 1];
            }
        }
        std::vector<int> suffix(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            if (customers[i] == 'Y') {
                suffix[i] = suffix[i + 1] + 1;
            } else {
                suffix[i] = suffix[i + 1];
            }
        }
        int penalty = INT_MAX;
        int result = -1;
        for (int i = 0; i <= n; ++i) {
            if (prefix[i] + suffix[i] < penalty) {
                result = i;
                penalty = prefix[i] + suffix[i];
            }
        }
        return result;
    }
};