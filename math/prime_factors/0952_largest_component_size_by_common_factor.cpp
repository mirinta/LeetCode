#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array of unique positive integers nums. Consider the following graph:
 *
 * - There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
 *
 * - There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common
 * factor greater than 1.
 *
 * Return the size of the largest connected component in the graph.
 *
 * ! 1 <= nums.length <= 2 * 10^4
 * ! 1 <= nums[i] <= 10^5
 * ! All the values of nums are unique.
 */

class UnionFind
{
public:
    explicit UnionFind(int n) : root(n), size(n, 1)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int find(int x)
    {
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    bool isConnected(int p, int q) { return find(p) == find(q); }

    void connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (size[rootQ] > size[rootP]) {
            root[rootP] = rootQ;
            size[rootQ] += size[rootP];
        } else {
            root[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
    }

private:
    std::vector<int> root;
    std::vector<int> size;
};

class Solution
{
public:
    int largestComponentSize(std::vector<int>& nums)
    {
        /** prime factors:   2   3   5   7
         *                  / \ / \ / \ /
         *           nums: 4   6   15  35
         */
        const int n = nums.size();
        const auto primes = getPrimes(*std::max_element(nums.begin(), nums.end()));
        const int m = primes.size();
        std::unordered_map<int, int> map;
        for (int j = 0; j < m; ++j) {
            map[primes[j]] = j;
        }
        UnionFind uf(n + m);
        for (int i = 0; i < n; ++i) {
            for (const auto& p : getPrimeFactors(nums[i], primes)) {
                uf.connect(i, n + map[p]);
            }
        }
        std::unordered_map<int, int> count;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            count[uf.find(i)]++;
            result = std::max(result, count[uf.find(i)]);
        }
        return result;
    }

private:
    std::vector<int> getPrimes(int n)
    {
        std::vector<int> isPrime(n + 1, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for (long long i = 2; i <= n; ++i) {
            if (isPrime[i]) {
                for (long long j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        std::vector<int> result;
        for (int i = 2; i <= n; ++i) {
            if (isPrime[i]) {
                result.push_back(i);
            }
        }
        return result;
    }

    std::vector<int> getPrimeFactors(int n, const std::vector<int>& primesTable)
    {
        std::vector<int> result;
        for (const auto& p : primesTable) {
            if (p > n)
                break;

            if (p * p > n) {
                result.push_back(n);
                break;
            }
            if (n % p == 0) {
                result.push_back(p);
                while (n % p == 0) {
                    n /= p;
                }
            }
        }
        return result;
    }
};
