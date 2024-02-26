/**
 * @brief Calculate a^b where b > 0.
 *
 * @note Time Complexity = O(logb)
 */
long long fastPow(long long a, long long b)
{
    long long result = 1;
    long long base = a;
    while (b > 0) {
        if (b & 1) {
            result *= base;
        }
        base *= base;
        b >>= 1;
    }
    return result;
}