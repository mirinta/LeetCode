#include <vector>

#include "fast_modular_exponentiation.cpp"

/**
 * @brief Return C(m, n) from a preprocessed table, which is calculated using the formula "C(m, n) =
 * C(m - 1, n) + C(m - 1, n - 1)".
 *
 * @note n <= m
 *
 * @note Time Complexity = O(mn), Space Complexity = O(mn)
 */
long long combModV1(long long m, long long n, long long mod = 1e9 + 7)
{
    std::vector<std::vector<long long>> memo(m + 1, std::vector<long long>(n + 1));
    for (int i = 0; i <= m; ++i) {
        memo[i][0] = 1;
    }
    for (int i = 0; i <= n; ++i) {
        memo[i][i] = 1;
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            memo[i][j] = (memo[i][j - 1] + memo[i - 1][j - 1]) % mod;
        }
    }
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
 * If gcd(p, a) = 1, then a^(p-1) ≡ 1 (% p).
 *
 * Therefore:
 * 1/m! % p = m!^(p-2) % p
 * 1/(m-1)! % p = (1/m! % p) * (m % p) % p
 * ...
 */
long long combModV2(long long m, long long n, long long mod = 1e9 + 7)
{
    std::vector<long long> factorial(m + 1, 1);
    for (long long i = 1; i <= m; ++i) {
        factorial[i] = factorial[i - 1] * i % mod;
    }
    std::vector<long long> invFactorial(m + 1);
    invFactorial[m] = fastPowMod(factorial[m], mod - 2, mod);
    for (long long i = m - 1; i >= 0; --i) {
        invFactorial[i] = invFactorial[i + 1] * (i + 1) % mod;
    }
    return factorial[m] * invFactorial[n] % mod * invFactorial[m - n] % mod;
}
