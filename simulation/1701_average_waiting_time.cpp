#include <vector>

/**
 * There is a restaurant with a single chef. You are given an array customers, where customers[i] =
 * [arrivali, timei]:
 *
 * - arrivali is the arrival time of the ith customer. The arrival times are sorted in
 * non-decreasing order.
 *
 * - timei is the time needed to prepare the order of the ith customer.
 *
 * When a customer arrives, he gives the chef his order, and the chef starts preparing it once he is
 * idle. The customer waits till the chef finishes preparing his order. The chef does not prepare
 * food for more than one customer at a time. The chef prepares food for customers in the order they
 * were given in the input.
 *
 * Return the average waiting time of all customers. Solutions within 10-5 from the actual answer
 * are considered accepted.
 *
 * ! 1 <= customers.length <= 10^5
 * ! 1 <= arrivali, timei <= 10^4
 * ! arrivali <= arrivali+1
 */

class Solution
{
public:
    double averageWaitingTime(std::vector<std::vector<int>>& customers)
    {
        const int n = customers.size();
        double waiting = 0;
        double ending = 0;
        for (const auto& customer : customers) {
            const double extra = std::max(0., ending - customer[0]);
            waiting += extra + customer[1];
            ending = extra + customer[0] + customer[1];
        }
        return waiting / n;
    }
};