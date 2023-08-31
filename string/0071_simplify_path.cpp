#include <string>
#include <vector>

/**
 * Given a string path, which is an absolute path (starting with a slash '/') to a file or directory
 * in a Unix-style file system, convert it to the simplified canonical path.
 *
 * In a Unix-style file system, a period '.' refers to the current directory, a double period '..'
 * refers to the directory up a level, and any multiple consecutive slashes (i.e. '//') are treated
 * as a single slash '/'. For this problem, any other format of periods such as '...' are treated as
 * file/directory names.
 *
 * The canonical path should have the following format:
 *
 * - The path starts with a single slash '/'.
 *
 * - Any two directories are separated by a single slash '/'.
 *
 * - The path does not end with a trailing '/'.
 *
 * - The path only contains the directories on the path from the root directory to the target file
 * or directory (i.e., no period '.' or double period '..')
 *
 * Return the simplified canonical path.
 *
 * ! 1 <= path.length <= 3000
 * ! path consists of English letters, digits, period '.', slash '/' or '_'.
 * ! path is a valid absolute Unix path.
 */

class Solution
{
public:
    std::string simplifyPath(std::string path)
    {
        const int n = path.size();
        std::vector<std::string> words;
        int i = 0;
        while (i < n) {
            while (i < n && path[i] == '/') {
                i++;
            }
            int j = i;
            while (j < n && path[j] != '/') {
                j++;
            }
            std::string word = path.substr(i, j - i);
            if (word == "..") {
                if (!words.empty()) {
                    words.pop_back();
                }
            } else if (!word.empty() && word != ".") {
                words.push_back(std::move(word));
            }
            i = j;
        }
        std::string result("/");
        for (int i = 0; i < words.size(); ++i) {
            result.append(std::move(words[i]));
            if (i < words.size() - 1) {
                result.push_back('/');
            }
        }
        return result;
    }
};