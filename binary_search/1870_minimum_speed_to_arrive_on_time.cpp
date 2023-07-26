#include <cmath>
#include <vector>

/**
 * You are given a floating-point number hour, representing the amount of time you have to reach the
 * office. To commute to the office, you must take n trains in sequential order. You are also given
 * an integer array dist of length n, where dist[i] describes the distance (in kilometers) of the
 * ith train ride.
 *
 * Each train can only depart at an integer hour, so you may need to wait in between each train
 * ride.
 *
 * - For example, if the 1st train ride takes 1.5 hours, you must wait for an additional 0.5 hours
 * before you can depart on the 2nd train ride at the 2 hour mark.
 *
 * Return the minimum positive integer speed (in kilometers per hour) that all the trains must
 * travel at for you to reach the office on time, or -1 if it is impossible to be on time.
 *
 * Tests are generated such that the answer will not exceed 107 and hour will have at most two
 * digits after the decimal point.
 *
 * ! n == dist.length
 * ! 1 <= n <= 10^5
 * ! 1 <= dist[i] <= 10^5
 * ! 1 <= hour <= 10^9
 * ! There will be at most two digits after the decimal point in hour.
 */

class Solution
{
public:
    int minSpeedOnTime(std::vector<int>& dist, double hour)
    {
        const int maxSpeed = getMaxSpeed(dist, hour);
        if (maxSpeed == -1)
            return -1;

        int lo = 1;
        int hi = maxSpeed;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, dist, hour)) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo > maxSpeed ? -1 : lo;
    }

private:
    int getMaxSpeed(const std::vector<int>& dist, double timeLimit)
    {
        if (dist.empty() || dist.size() - 1 >= timeLimit)
            return -1;

        int maxSpeed = std::ceil(dist.back() / (timeLimit - dist.size() + 1));
        for (int i = 0; i < dist.size() - 1; ++i) {
            maxSpeed = std::max(maxSpeed, dist[i]);
        }
        return maxSpeed;
    }

    bool isValid(int speed, std::vector<int>& dist, double timeLimit)
    {
        double time = 0;
        for (int i = 0; i < dist.size(); ++i) {
            if (i == dist.size() - 1) {
                time += dist[i] * 1.0 / speed;
            } else {
                time += std::ceil(dist[i] * 1.0 / speed);
            }
            if (time > timeLimit)
                return false;
        }
        return true;
    }
};