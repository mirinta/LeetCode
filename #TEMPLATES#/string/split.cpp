#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& str, char separator)
{
    std::istringstream stream(str);
    std::string s;
    std::vector<std::string> result;
    while (std::getline(stream, s, separator)) {
        result.push_back(s);
    }
    return result;
}