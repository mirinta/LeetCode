/**
 * @brief Calculate a^b % mod.
 *
 * @note Time Complexity = O(logb)
 */
long long fastPowMod(long long a, long long b, long long mod = 1e9 + 7)
{
    long long result = 1;
    long long base = a;
    while (b > 0) {
        if (b & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        b >>= 1;
    }
    return result;
}
