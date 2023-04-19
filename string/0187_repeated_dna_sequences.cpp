#include <string>
#include <unordered_map>
#include <vector>

/**
 * The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G' and 'T'.
 *
 * - For example, "ACGAATTCCG" is a DNA sequence.
 *
 * When studying DNA, it is useful to identify repeated sequences within the DNA.
 *
 * Given a string "s" that represents a DNA sequence, return all the "10-letter-long" sequences
 * (substrings) that occur more than once in a DNA molecule. You may return the answer in any order.
 */

class Solution
{
public:
    std::vector<std::string> findRepeatedDnaSequences(const std::string& s)
    {
        constexpr int kSeqLength = 10;
        if (s.empty() || s.size() < kSeqLength)
            return {};

        std::unordered_map<std::string, int> freq;
        for (size_t i = 0; i <= s.size() - kSeqLength; ++i) {
            freq[s.substr(i, kSeqLength)]++;
        }
        std::vector<std::string> result;
        for (const auto& [str, count] : freq) {
            if (count > 1) {
                result.push_back(str);
            }
        }
        return result;
    }
};