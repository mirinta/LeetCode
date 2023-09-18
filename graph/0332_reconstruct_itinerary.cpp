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
        return approach2(tickets);
    }

private:
    // graph[from] = {<to, ticketID>, ...}
    using Graph = std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>;

    // Eulerian Path
    std::vector<std::string> approach2(const std::vector<std::vector<std::string>>& tickets)
    {
        Graph graph;
        for (int i = 0; i < tickets.size(); ++i) {
            const auto& from = tickets[i][0];
            const auto& to = tickets[i][1];
            graph[from].emplace_back(to, i);
        }
        std::unordered_map<std::string, int> outdegrees;
        for (auto& [from, adjacencies] : graph) {
            std::sort(adjacencies.begin(), adjacencies.end(),
                      [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
            outdegrees[from] += adjacencies.size();
        }
        // the problem guarantees the existence of Eulerian path
        std::unordered_set<int> usedTickets;
        std::vector<std::string> result;
        dfs(result, usedTickets, outdegrees, "JFK", graph);
        std::reverse(result.begin(), result.end());
        return result;
    }

    void dfs(std::vector<std::string>& result, std::unordered_set<int>& usedTickets,
             std::unordered_map<std::string, int>& outdegrees, const std::string& start,
             const Graph& graph)
    {
        while (outdegrees[start] > 0) {
            for (const auto& [to, ticketID] : graph.at(start)) {
                if (!usedTickets.count(ticketID)) {
                    usedTickets.insert(ticketID);
                    outdegrees[start]--;
                    dfs(result, usedTickets, outdegrees, to, graph);
                }
            }
        }
        result.push_back(start);
    }

    // Backtracking
    std::vector<std::string> approach1(const std::vector<std::vector<std::string>>& tickets)
    {
        Graph graph;
        std::unordered_set<int> remainingTickets;
        for (int i = 0; i < tickets.size(); ++i) {
            const auto& from = tickets[i][0];
            const auto& to = tickets[i][1];
            graph[from].emplace_back(to, i);
            remainingTickets.insert(i);
        }
        for (auto& [from, adjacencies] : graph) {
            std::sort(adjacencies.begin(), adjacencies.end(),
                      [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
        }
        const std::string kStart{"JFK"};
        std::vector<std::string> result{kStart};
        backtrack(result, remainingTickets, kStart, graph);
        return result;
    }

    // return true if there is no remaining ticket
    bool backtrack(std::vector<std::string>& result, std::unordered_set<int>& remainingTickets,
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
            if (backtrack(result, remainingTickets, to, graph))
                return true;

            remainingTickets.insert(ticketID);
            result.pop_back();
        }
        return false;
    }
};
