#include <vector>

/**
 * Write a function that reverses a string. The input string is given as an array of characters "s".
 *
 * You must do this by modifying the input array in-place with O(1) extra memory.
 */

class Solution
{
public:
    void reverseString(std::vector<char>& s)
    {
        // two pointers:
        // - forward: iterate from begin to end
        // - backward: iterate from end to begin
        // - swap elements at forward and backward
        // - when forward meets backward, done
        const auto size = s.size();
        if (size <= 1)
            return;

        size_t forward = 0;
        size_t backward = size - 1;
        while (forward < backward) {
            std::swap(s[forward++], s[backward--]);
        }
    }
};