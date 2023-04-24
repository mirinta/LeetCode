#include <stack>
#include <string>
#include <unordered_map>
#include <utility>

/**
 * Given a string "s", return the lexicographically smallest subsequence of "s" that contains all
 * the distinct characters of "s" exactly once.
 *
 * ! This problem is teh same as 316.
 */

class Solution
{
public:
    std::string smallestSubsequence(const std::string& s)
    {
        if (s.empty() || s.size() == 1)
            return s;
        // char -> frequency, isChecked
        std::unordered_map<char, std::pair<int, bool>> freq;
        for (const auto& c : s) {
            if (freq.count(c)) {
                freq[c].first++;
            } else {
                freq[c] = std::make_pair(1, false);
            }
        }
        // store the final result in reverse order
        std::stack<char> stack;
        for (const auto& c : s) {
            freq[c].first--;
            if (freq[c].second) // the character is already checked
                continue;

            // rearrange the stack
            while (!stack.empty() && stack.top() > c) {
                const auto character = stack.top();
                // do not pop if there's no same character in the subsequence
                if (freq[character].first == 0)
                    break;

                stack.pop();
                freq[character].second = false;
            }
            stack.push(c);
            freq[c].second = true;
        }
        std::string result = "";
        for (; !stack.empty(); stack.pop()) {
            result += stack.top();
        }
        reverse(result);
        return result;
    }

private:
    void reverse(std::string& s)
    {
        if (s.empty() || s.size() == 1)
            return;

        for (size_t left = 0, right = s.size() - 1; left < right; ++left, --right) {
            std::swap(s[left], s[right]);
        }
    }
};