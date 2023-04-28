#include <stack>
#include <string>
#include <unordered_map>
#include <utility>

/**
 * Given a string "s", remove duplicate letters so that every letter appears once and only once. You
 * must make sure your result is the smallest n lexicographical order among all possible results.
 *
 * A string "a" is lexicographically smaller than a string "b" if the first position where "a" and
 * "b" differ, string "a" has a letter that appears earlier in the alphabet than the corresponding
 * letter in "b". If the first "min(a.length, b.length)" characters do not differ, then the shorter
 * string is the lexicographically smaller one.
 *
 * https://mp.weixin.qq.com/s/Yq49ZBEW3DJx6nXk1fMusw
 *
 * ! This problem is the same as 1081.
 */

class Solution
{
public:
    std::string removeDuplicateLetters(const std::string& s)
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
