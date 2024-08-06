#include <string>
#include <vector>

/**
 * @brief Assume s contains only lowercase English letters.
 */
class RangeHash
{
    using LLONG = long long;

    static constexpr LLONG kMod = 1e9 + 7;
    static constexpr LLONG kBase = 26;

public:
    static LLONG valueOf(char c) { return c - 'a' + 1; }

    explicit RangeHash(const std::string& s) : prefixHash(s.size() + 1), powMod(s.size() + 1)
    {
        powMod[0] = 1;
        for (int i = 1; i <= s.size(); ++i) {
            prefixHash[i] = (prefixHash[i - 1] * kBase % kMod + valueOf(s[i - 1]) % kMod) % kMod;
            powMod[i] = powMod[i - 1] * kBase % kMod;
        }
    }

    // let L = right - left + 1
    // hash[left:right] = s[left] * Base^(L-1) + ... + s[right] * Base^0
    // where left and right are 0-indexed
    LLONG query(int left, int right) const
    {
        LLONG result = prefixHash[right + 1] - prefixHash[left] * powMod[right - left + 1] % kMod;
        result = (result + kMod) % kMod; // +kMod to prevent negative value
        return result;
    }

private:
    std::vector<LLONG> prefixHash; // prefixHash[i] = s[0] * Base^(i-1) + ... + s[i-1] * Base^0
    std::vector<LLONG> powMod;     // Base^i
};
