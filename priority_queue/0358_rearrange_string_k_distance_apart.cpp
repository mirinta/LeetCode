#include <queue>
#include <string>
#include <unordered_map>

/**
 * Given a string s and an integer k, rearrange s such that the same characters are at least
 * distance k from each other. If it is not possible to rearrange the string, return an empty string
 * "".
 *
 * ! 1 <= s.length <= 3 * 10^5
 * ! s consists of only lowercase English letters.
 * ! 0 <= k <= s.length
 */

class Solution
{
public:
    std::string rearrangeString(std::string s, int k)
    {
        if (k == 0)
            return s;

        using Pair = std::pair<char, int>; // character and frequency
        // pick the most k frequent characters,
        // if there's a tie, pick the smaller one
        auto comparator = [](const auto& p1, const auto& p2) {
            return p1.second == p2.second ? p1.first > p2.first : p1.second < p2.second;
        };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator);
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        for (auto& pair : map) {
            pq.push(std::move(pair));
        }
        std::string result;
        while (!pq.empty()) {
            // fewer than k characters,
            // the only valid case is when the frequency of each character is exactly 1
            // e.g. k=3, but we have three a's and two b's left, it is impossible to rearrange these
            // characters
            if (pq.size() < k && pq.top().second > 1)
                return {};

            std::vector<Pair> pairs(std::min<int>(k, pq.size()));
            for (auto& pair : pairs) {
                pair = std::move(pq.top());
                pq.pop();
                result.push_back(pair.first);
                pair.second--;
            }
            for (auto& pair : pairs) {
                if (pair.second > 0) {
                    pq.push(std::move(pair));
                }
            }
        }
        return result;
    }
};