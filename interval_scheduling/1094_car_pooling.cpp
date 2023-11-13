#include <algorithm>
#include <vector>

/**
 * There is a car with capacity empty seats. The vehicle only drives east (i.e., it cannot turn
 * around and drive west).
 *
 * You are given the integer capacity and an array trips where trips[i] = [numPassengersi, fromi,
 * toi] indicates that the ith trip has numPassengersi passengers and the locations to pick them up
 * and drop them off are fromi and toi respectively. The locations are given as the number of
 * kilometers due east from the car's initial location.
 *
 * Return true if it is possible to pick up and drop off all passengers for all the given trips, or
 * false otherwise.
 *
 * ! 1 <= trips.length <= 1000
 * ! trips[i].length == 3
 * ! 1 <= numPassengersi <= 100
 * ! 0 <= fromi < toi <= 1000
 * ! 1 <= capacity <= 10^5
 */

class Solution
{
public:
    bool carPooling(std::vector<std::vector<int>>& trips, int capacity)
    {
        std::vector<std::pair<int, int>> timestamps; // <location, passengers>
        for (const auto& trip : trips) {
            timestamps.emplace_back(trip[1], trip[0]);
            timestamps.emplace_back(trip[2], -trip[0]);
        }
        std::sort(timestamps.begin(), timestamps.end());
        int count = 0;
        for (const auto& [location, passengers] : timestamps) {
            count += passengers;
            if (count > capacity)
                return false;
        }
        return true;
    }
};