#include <queue>
#include <vector>

/**
 * You are given an integer array heights representing the heights of buildings, some bricks, and
 * some ladders.
 *
 * You start your journey from building 0 and move to the next building by possibly using bricks or
 * ladders.
 *
 * While moving from building i to building i+1 (0-indexed),
 *
 * - If the current building's height is greater than or equal to the next building's height, you do
 * not need a ladder or bricks.
 *
 * - If the current building's height is less than the next building's height, you can either use
 * one ladder or (h[i+1] - h[i]) bricks.
 *
 * Return the furthest building index (0-indexed) you can reach if you use the given ladders and
 * bricks optimally.
 *
 * ! 1 <= heights.length <= 10^5
 * ! 1 <= heights[i] <= 10^6
 * ! 0 <= bricks <= 10^9
 * ! 0 <= ladders <= heights.length
 */

class Solution
{
public:
    int furthestBuilding(std::vector<int>& heights, int bricks, int ladders)
    {
        // min heap
        std::priority_queue<int, std::vector<int>, std::greater<>> pq;
        for (int i = 1; i < heights.size(); ++i) {
            // we are standing at building i-1
            const int diff = heights[i] - heights[i - 1];
            if (diff <= 0)
                continue;

            // store height difference to rearrange the usage of ladders and bricks
            pq.push(diff);
            if (ladders > 0) {
                // we have enough ladders, use ladder first
                ladders--;
            } else if (bricks < pq.top()) {
                // not enough bricks and ladders, return the building we are standing at
                return i - 1;
            } else {
                // we only have bricks
                // find the min diff, replace that ladder with bricks
                // then we have one ladder to move to building i
                bricks -= pq.top();
                pq.pop();
            }
        }
        return heights.size() - 1; // furthest building index
    }
};
