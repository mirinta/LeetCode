#include <vector>

/**
 * We have n buildings numbered from 0 to n - 1. Each building has a number of employees. It's
 * transfer season, and some employees want to change the building they reside in.
 *
 * You are given an array requests where requests[i] = [from_i, to_i] represents an employee's
 * request to transfer from building from_i to building to_i.
 *
 * All buildings are full, so a list of requests is achievable only if for each building, the net
 * change in employee transfers is zero. This means the number of employees leaving is equal to the
 * number of employees moving in. For example if n = 3 and two employees are leaving building 0, one
 * is leaving building 1, and one is leaving building 2, there should be two employees moving to
 * building 0, one employee moving to building 1, and one employee moving to building 2.
 *
 * Return the maximum number of achievable requests.
 *
 * ! 1 <= n <= 20
 * ! 1 <= requests.length <= 16
 * ! requests[i].length == 2
 * ! 0 <= from_i, to_i < n
 */

class Solution
{
public:
    int maximumRequests(int n, std::vector<std::vector<int>>& requests)
    {
        return approach2(n, requests);
    }

private:
    // approach 2: bit mask
    int approach2(int n, std::vector<std::vector<int>>& requests)
    {
        int result = 0;
        for (int state = (1 << requests.size()) - 1; state >= 0; --state) {
            if (isValid(state, n, requests)) {
                result = std::max(result, numOfBinaryOnes(state));
            }
        }
        return result;
    }

    bool isValid(int state, const int n, const std::vector<std::vector<int>>& requests)
    {
        std::vector<int> netChange(n, 0);
        for (int i = 0; state; state >>= 1, ++i) {
            if (state & 1) {
                netChange[requests[i][0]]--;
                netChange[requests[i][1]]++;
            }
        }
        for (const auto& val : netChange) {
            if (val != 0)
                return false;
        }
        return true;
    }

    int numOfBinaryOnes(int n)
    {
        int num = 0;
        while (n) {
            num++;
            n &= n - 1;
        }
        return num;
    }

    // approach 1 : backtracking
    int approach1(int n, std::vector<std::vector<int>>& requests)
    {
        std::vector<int> netChange(n, 0);
        int result = 0;
        backtrack(netChange, result, 0, 0, requests);
        return result;
    }

    void backtrack(std::vector<int>& netChange, int& result, int count, int requestID,
                   const std::vector<std::vector<int>>& requests)
    {
        if (requestID == requests.size()) {
            for (const auto& val : netChange) {
                if (val != 0)
                    return;
            }
            result = std::max(result, count);
            return;
        }
        const int from = requests[requestID][0];
        const int to = requests[requestID][1];
        netChange[to]++;
        netChange[from]--;
        backtrack(netChange, result, count + 1, requestID + 1, requests);
        netChange[to]--;
        netChange[from]++;
        backtrack(netChange, result, count, requestID + 1, requests);
    }
};