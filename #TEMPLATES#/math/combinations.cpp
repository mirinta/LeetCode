#include <array>
#include <mutex>
#include <vector>

#include "fast_modular_exponentiation.cpp"

/**
 * @brief Return C(m, n) from a preprocessed table, which is calculated using the formula "C(m, n) =
 * C(m - 1, n) + C(m - 1, n - 1)".
 *
 * @note n <= m <= 1000
 *
 * @note Time Complexity = O(mn), Space Complexity = O(mn)
 */
long long combinations(long long m, long long n)
{
    static constexpr int D = 1001;
    using Memo = std::array<std::array<long long, D>, D>;
    static Memo memo;
    static std::once_flag flag;
    std::call_once(
        flag,
        [](Memo& memo) {
            for (int i = 0; i < memo.size(); ++i) {
                memo[i][i] = 1;
                memo[i][0] = 1;
                for (int j = 1; i > 0 && j < memo.size(); ++j) {
                    memo[i][j] = memo[i - 1][j] + memo[i - 1][j - 1];
                }
            }
        },
        memo);

    return memo[m][n];
}

/**
 * @brief Calculate C(m, n) % mod on demand using the formula "C(m, n) = m! / n!(m - n)!".
 *
 * @note m >= n
 *
 * @note Time Complexity = O(m), Space Complexity = O(m)
 *
 * @details
 * answer = (m!/n! % mod) * (1/(m-n)! % mod) % mod
 * answer = (m! % mod) * (1/n! % mod) % mod * (1/(m-n)! % mod) % mod
 *
 * Fermat's Little Theorem:
 * If p is a prime number, then for any integer a, a^p ≡ a (% p).
 * If gcd(p, a) = 1, then a^(p-1) ≡ 1 (% p)
 *
 * According to the above theorem, a^(p-1) % p = (a^(p-2) % p) * (a % p) % p = 1,
 * i.e., a^(p-2) is the multiplicative inverse of a.
 */
long long combinationsMod(long long m, long long n, long long mod = 1e9 + 7)
{
    std::vector<long long> factorial(m + 1, 1);
    for (long long i = 1; i <= m; ++i) {
        factorial[i] = factorial[i - 1] * i % mod;
    }
    std::vector<long long> invFactorial(m + 1);
    invFactorial[n] = fastPowMod(factorial[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; --i) {
        invFactorial[i] = invFactorial[i + 1] * (i + 1) % mod;
    }
    return factorial[m] * invFactorial[n] % mod * invFactorial[m - n] % mod;
}
