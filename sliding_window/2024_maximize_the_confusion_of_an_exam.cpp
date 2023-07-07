#include <string>

/**
 * A teacher is writing a test with n true/false questions, with 'T' denoting true and 'F' denoting
 * false. He wants to confuse the students by maximizing the number of consecutive questions with
 * the same answer (multiple trues or multiple falses in a row).
 *
 * You are given a string answerKey, where answerKey[i] is the original answer to the ith question.
 * In addition, you are given an integer k, the maximum number of times you may perform the
 * following operation:
 *
 * - Change the answer key for any question to 'T' or 'F' (i.e., set answerKey[i] to 'T' or 'F').
 *
 * Return the maximum number of consecutive 'T's or 'F's in the answer key after performing the
 * operation at most k times.
 *
 * ! n == answerKey.length
 * ! 1 <= n <= 5 * 10^4
 * ! answerKey[i] is either 'T' or 'F'
 * ! 1 <= k <= n
 */

class Solution
{
public:
    int maxConsecutiveAnswers(std::string answerKey, int k) { return approach2(answerKey, k); }

private:
    int approach2(const std::string& s, int k)
    {
        // sliding window, one pass
        int result = 0;
        for (int left = 0, right = 0, countF = 0, countT = 0; right < s.size(); ++right) {
            if (s[right] == 'F') {
                countF++;
            } else {
                countT++;
            }
            while (std::min(countT, countF) > k) {
                if (s[left] == 'F') {
                    countF--;
                } else {
                    countT--;
                }
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }

    int approach1(const std::string& s, int k)
    {
        // sliding window, two pass
        return std::max(maxConsecutiveLetter(s, 'F', k), maxConsecutiveLetter(s, 'T', k));
    }

    int maxConsecutiveLetter(const std::string& s, char targetLetter, int maxOperations)
    {
        int result = 0;
        for (int left = 0, right = 0, count = 0; right < s.size(); ++right) {
            if (s[right] == targetLetter) {
                count++;
            }
            while (count > maxOperations) {
                if (s[left++] == targetLetter) {
                    count--;
                }
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};