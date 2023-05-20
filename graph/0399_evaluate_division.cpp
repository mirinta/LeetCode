#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given array of variable pairs "equations" and an array of real numbers "values", where
 * equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi
 * is a string that represents a single variable.
 *
 * You are also given some "queries", where queries[j] = [Cj, Dj] represents jth query where you
 * must find the answer for Cj / Dj = ?
 *
 * Return the answers to all queries. If a single answer cannot be determined, return -1.0.
 *
 * Note: The input is always valid. You may assume that evaluating the queries will not result in
 * division by zero and that there is no contradiction.
 *
 * Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0],
 * queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
 * Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
 * Explanation: Given: a / b = 2.0, b / c = 3.0 queries are:
 * a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
 */

class Solution
{
public:
    std::vector<double> calcEquation(std::vector<std::vector<std::string>>& equations,
                                     std::vector<double>& values,
                                     std::vector<std::vector<std::string>>& queries)
    {
        Graph graph;
        for (size_t i = 0; i < equations.size(); ++i) {
            const auto& dividend = equations[i][0];
            const auto& divisor = equations[i][1];
            const auto& quotient = values[i];
            graph[dividend].push_back({divisor, quotient});
            graph[divisor].push_back({dividend, 1 / quotient});
        }
        std::vector<double> result;
        for (const auto& query : queries) {
            const auto& dividend = query[0];
            const auto& divisor = query[1];
            if (!graph.count(dividend) || !graph.count(divisor)) {
                result.push_back(-1);
                continue;
            }
            if (dividend == divisor) {
                result.push_back(1);
                continue;
            }
            std::unordered_set<std::string> visited;
            result.push_back(compute(visited, 1, dividend, divisor, graph));
        }
        return result;
    }

private:
    using Graph = std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>;
    double compute(std::unordered_set<std::string>& visited, double product, const std::string& s,
                   const std::string& t, const Graph& graph)
    {
        if (s == t)
            return product;

        visited.insert(s);
        double result = -1;
        for (const auto& [adj, val] : graph.at(s)) {
            if (visited.count(adj))
                continue;

            result = compute(visited, product * val, adj, t, graph);
            if (result != -1)
                break;
        }
        visited.erase(s);
        return result;
    }
};