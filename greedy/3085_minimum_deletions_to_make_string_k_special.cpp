#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a string word and an integer k.
 *
 * We consider word to be k-special if |freq(word[i]) - freq(word[j])| <= k for all indices i and j
 * in the string.
 *
 * Here, freq(x) denotes the frequency of the character x in word, and |y| denotes the absolute
 * value of y.
 *
 * Return the minimum number of characters you need to delete to make word k-special.
 *
 * ! 1 <= word.length <= 10^5
 * ! 0 <= k <= 10^5
 * ! word consists only of lowercase English letters.
 */

class Solution
{
public:
    int minimumDeletions(std::string word, int k)
    {
        std::unordered_map<char, int> map;
        for (const auto& c : word) {
            map[c]++;
        }
        std::vector<int> frequencies;
        for (const auto& [c, freq] : map) {
            frequencies.push_back(freq);
        }
        const int n = frequencies.size();
        std::sort(frequencies.begin(), frequencies.end());
        int sum = 0;
        int result = word.size();
        // choose frequencies[i] as the minimum frequency
        // we need to remove frequencies[0:i-1] and
        // check frequencies[i+1:j]
        for (int i = 0; i < n; ++i) {
            int remove = sum;
            for (int j = n - 1; j > i; --j) {
                if (frequencies[j] - frequencies[i] <= k)
                    break;

                remove += frequencies[j] - frequencies[i] - k;
            }
            result = std::min(result, remove);
            sum += frequencies[i];
        }
        return result;
    }
};