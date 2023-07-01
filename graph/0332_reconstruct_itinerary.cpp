#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given a list of airline tickets where tickets[i] = [from_i, to_i] represent the departure
 * and the arrival airports of one flight. Reconstruct the itinerary in order and return it.
 *
 * All of the tickets belong to a man who departs from "JFK", thus, the itinerary must begin with
 * "JFK". If there are multiple valid itineraries, you should return the itinerary that has the
 * smallest lexical order when read as a single string.
 *
 * For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
 * You may assume all tickets form at least one valid itinerary. You must use all the tickets once
 * and only once.
 *
 * ! 1 <= tickets.length <= 300
 * ! tickets[i].length == 2
 * ! from_i.length == 3
 * ! to_i.length == 3
 * ! from_i and to_i consist of uppercase English letters.
 * ! from_i != to_i
 */

class Solution
{
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets)
    {
        Graph graph;
        std::unordered_set<int> remainingTickets;
        for (int i = 0; i < tickets.size(); ++i) {
            graph[tickets[i][0]].push_back({tickets[i][1], i});
            remainingTickets.insert(i);
        }
        for (auto& [from, adjacency] : graph) {
            std::sort(adjacency.begin(), adjacency.end());
        }
        const std::string kStart{"JFK"};
        std::vector<std::string> result{kStart};
        backtrack(remainingTickets, result, kStart, graph);
        return result;
    }

private:
    using Graph = std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>;

    // return true if the final result is found, i.e., there is no remaining ticket
    bool backtrack(std::unordered_set<int>& remainingTickets, std::vector<std::string>& result,
                   const std::string& from, const Graph& graph)
    {
        if (remainingTickets.empty())
            return true;

        if (!graph.count(from))
            return false;

        for (const auto& [to, ticketID] : graph.at(from)) {
            if (!remainingTickets.count(ticketID))
                continue; // this ticket is already used

            remainingTickets.erase(ticketID);
            result.push_back(to);
            if (backtrack(remainingTickets, result, to, graph))
                return true;

            remainingTickets.insert(ticketID);
            result.pop_back();
        }
        return false;
    }
};