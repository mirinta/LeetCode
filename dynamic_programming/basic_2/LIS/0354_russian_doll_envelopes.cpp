#include <algorithm>
#include <vector>

/**
 * You are given a 2D array of integers "envelopes" where "envelopes[i] = [wi, hi]" represents the
 * width and the height of an envelope.
 *
 * One envelope can fit into another if and only if both the width and the height of one envelope
 * are greater than the other envelope's width and height.
 *
 * Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
 *
 * ! Note: you cannot rotate an envelope.
 *
 * ! 1 <= envelopes.length <= 10^5
 * ! envelopes[i].length == 2
 * ! 1 <= wi, hi <= 10^5
 */

class Solution
{
public:
    int maxEnvelopes(std::vector<std::vector<int>>& envelopes)
    {
        // sort widths in ascending order,
        // if two envelopes has the same width, sort heights in decreasing order
        std::sort(envelopes.begin(), envelopes.end(), [](const auto& v1, const auto& v2) {
            return v1[0] == v2[0] ? v1[1] > v2[1] : v1[0] < v2[0];
        });
        // find length of the LIS among heights
        std::vector<int> vec; // strictly increasing
        for (const auto& envelope : envelopes) {
            const auto& height = envelope[1];
            if (vec.empty() || height > vec.back()) {
                vec.push_back(height);
            } else {
                // find the first index s.t. vec[index] >= height
                auto iter = std::lower_bound(vec.begin(), vec.end(), height);
                if (iter != vec.end()) {
                    *iter = height;
                }
            }
        }
        return vec.size();
    }
};
