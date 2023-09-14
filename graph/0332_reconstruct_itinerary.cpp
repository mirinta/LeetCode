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
        std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> graph;
        std::unordered_set<int> remainingTickets;
        for (int i = 0; i < tickets.size(); ++i) {
            const auto& from = tickets[i][0];
            const auto& to = tickets[i][1];
            graph[from].push_back({to, i});
            remainingTickets.insert(i);
        }
        for (auto& [from, adjacencies] : graph) {
            std::sort(adjacencies.begin(), adjacencies.end());
        }
        const std::string kStart{"JFK"};
        std::vector<std::string> result{kStart};
        backtrack(result, remainingTickets, kStart, graph);
        return result;
    }

private:
    // return true if there is no remaining ticket, i.e., the final answer is found
    bool backtrack(
        std::vector<std::string>& result, std::unordered_set<int>& remainingTickets,
        const std::string& from,
        const std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& graph)
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
            if (backtrack(result, remainingTickets, to, graph))
                return true;

            remainingTickets.insert(ticketID);
            result.pop_back();
        }
        return false;
    }
};
