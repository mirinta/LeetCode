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
    // bitmask
    int approach2(int n, const std::vector<std::vector<int>>& requests)
    {
        int result = 0;
        for (int state = (1 << requests.size()) - 1; state > 0; --state) {
            if (isValid(state, n, requests)) {
                result = std::max(result, binaryOnes(state));
            }
        }
        return result;
    }

    bool isValid(int state, int n, const std::vector<std::vector<int>>& requests)
    {
        int netChange[n];
        std::memset(netChange, 0, sizeof(netChange));
        int i = 0;
        while (state) {
            if (state & 1) {
                netChange[requests[i][0]]--;
                netChange[requests[i][1]]++;
            }
            state >>= 1;
            i++;
        }
        for (const auto& val : netChange) {
            if (val != 0)
                return false;
        }
        return true;
    }

    int binaryOnes(int num)
    {
        int result = 0;
        while (num) {
            num &= num - 1;
            result++;
        }
        return result;
    }

    // backtrack
    int approach1(int n, const std::vector<std::vector<int>>& requests)
    {
        std::vector<int> netChange(n, 0);
        int result = 0;
        backtrack(result, netChange, 0, 0, requests);
        return result;
    }

    void backtrack(int& result, std::vector<int>& netChange, int requestID, int count,
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
        const auto& from = requests[requestID][0];
        const auto& to = requests[requestID][1];
        // case 1: execute this request
        netChange[from]--;
        netChange[to]++;
        backtrack(result, netChange, requestID + 1, count + 1, requests);
        netChange[from]++; // restore
        netChange[to]--;   // restore
        // case 2: ignore this request
        backtrack(result, netChange, requestID + 1, count, requests);
    }
};
