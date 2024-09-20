#include <string>
#include <vector>

/**
 * @brief: valueOf(a) = 1,
 *         valueOf(b) = 2,
 *         ...
 *         valueOf(z) = 26
 * @param base: let base = 26
 * @param mod: let mod = 1e9 + 7
 * @param L: fixed length of substrings of s
 * @param s: s contains only lowercase English letters
 * @return: hash of each fixed length substring of s
 */
std::vector<long long> rollingHash(long long base, long long mod, long long L, const std::string& s)
{
    // low level                    high level
    // ----------------------------->
    // 0 ... n-k-1 n-k ... n-2 n-1
    //             |<---hash1--->|
    //       |<----hash2---->|
    // <----------------------------- traverse
    // given hash1, calculate hash2

    auto valueOf = [](char c) -> long long { return c - 'a' + 1; };
    const long long n = s.size();
    long long powMod = 1; // base^(L-1) % mod
    for (long long i = 1; i <= L - 1; ++i) {
        powMod = powMod * base % mod;
    }
    long long hash = 0;
    std::vector<long long> result;
    for (long long i = n - 1; i >= 0; --i) {
        if (i < n - L) {
            hash = (hash - (valueOf(s[i + L]) % mod * powMod) % mod + mod) % mod;
        }
        hash = (hash * (base % mod)) % mod;
        hash = (hash + valueOf(s[i]) % mod) % mod;
        result.push_back(hash);
    }
    return result;
}
