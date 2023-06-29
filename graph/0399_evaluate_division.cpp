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
        BiGraph graph;
        for (int i = 0; i < equations.size(); ++i) {
            const auto& numerator = equations[i][0];
            const auto& denominator = equations[i][1];
            const auto& quotient = values[i];
            graph[numerator][denominator] = quotient;
            graph[denominator][numerator] = 1 / quotient;
        }
        std::vector<double> result;
        std::unordered_set<std::string> visited;
        for (const auto& query : queries) {
            const auto& numerator = query[0];
            const auto& denominator = query[1];
            if (!graph.count(numerator) || !graph.count(denominator)) {
                result.push_back(-1);
                continue;
            }
            if (numerator == denominator) {
                result.push_back(1);
                continue;
            }
            visited.clear();
            result.push_back(backtrack(visited, 1, numerator, denominator, graph));
        }
        return result;
    }

private:
    // graph[i][j] = result of i/j
    using BiGraph = std::unordered_map<std::string, std::unordered_map<std::string, double>>;

    double backtrack(std::unordered_set<std::string>& visited, double product,
                     const std::string& current, const std::string& target, const BiGraph& graph)
    {
        if (current == target)
            return product;

        double result = -1;
        visited.insert(current);
        for (const auto& [adj, val] : graph.at(current)) {
            if (visited.count(adj))
                continue;

            result = backtrack(visited, product * val, adj, target, graph);
            if (result != -1)
                break;
        }
        visited.erase(current);
        return result;
    }
};
