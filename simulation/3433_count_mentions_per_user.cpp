#include <sstream>
#include <string>
#include <vector>

/**
 * You are given an integer numberOfUsers representing the total number of users and an array events
 * of size n x 3.
 *
 * Each events[i] can be either of the following two types:
 *
 * 1. Message Event: ["MESSAGE", "timestampi", "mentions_stringi"]
 *
 * - This event indicates that a set of users was mentioned in a message at timestampi.
 *
 * - The mentions_stringi string can contain one of the following tokens:
 *
 *   - id<number>: where <number> is an integer in range [0,numberOfUsers - 1]. There can be
 *     multiple ids separated by a single whitespace and may contain duplicates. This can mention
 *     even the offline users.
 *
 *   - ALL: mentions all users.
 *
 *   - HERE: mentions all online users.
 *
 * 2. Offline Event: ["OFFLINE", "timestampi", "idi"]
 *
 * - This event indicates that the user idi had become offline at timestampi for 60 time units. The
 * user will automatically be online again at time timestampi + 60.
 *
 * Return an array mentions where mentions[i] represents the number of mentions the user with id i
 * has across all MESSAGE events.
 *
 * All users are initially online, and if a user goes offline or comes back online, their status
 * change is processed before handling any message event that occurs at the same timestamp.
 *
 * Note that a user can be mentioned multiple times in a single message event, and each mention
 * should be counted separately.
 *
 * ! 1 <= numberOfUsers <= 100
 * ! 1 <= events.length <= 100
 * ! events[i].length == 3
 * ! events[i][0] will be one of MESSAGE or OFFLINE.
 * ! 1 <= int(events[i][1]) <= 10^5
 * ! The number of id<number> mentions in any "MESSAGE" event is between 1 and 100.
 * ! 0 <= <number> <= numberOfUsers - 1
 * ! It is guaranteed that the user id referenced in the OFFLINE event is online at the time the
 * ! event occurs.
 */

class Solution
{
public:
    std::vector<int> countMentions(int numberOfUsers, std::vector<std::vector<std::string>>& events)
    {
        std::sort(events.begin(), events.end(), [](const auto& e1, const auto& e2) {
            if (std::stoi(e1[1]) == std::stoi(e2[1]))
                return e1[0] == "OFFLINE";

            return std::stoi(e1[1]) < std::stoi(e2[1]);
        });
        std::vector<int> online(numberOfUsers, 0);
        std::vector<int> result(numberOfUsers, 0);
        for (const auto& e : events) {
            if (e[0] == "MESSAGE" && e[2] == "ALL") {
                for (int i = 0; i < numberOfUsers; ++i) {
                    result[i]++;
                }
            } else if (e[0] == "MESSAGE" && e[2] == "HERE") {
                for (int i = 0; i < numberOfUsers; ++i) {
                    result[i] += online[i] <= std::stoi(e[1]);
                }
            } else if (e[0] == "OFFLINE") {
                online[std::stoi(e[2])] = std::stoi(e[1]) + 60;
            } else {
                for (const auto& i : split(e[2])) {
                    result[i]++;
                }
            }
        }
        return result;
    }

private:
    std::vector<int> split(const std::string& str)
    {
        std::vector<int> result;
        std::istringstream stream(str);
        std::string s;
        while (std::getline(stream, s, ' ')) {
            result.push_back(std::stoi(s.substr(2)));
        }
        return result;
    }
};