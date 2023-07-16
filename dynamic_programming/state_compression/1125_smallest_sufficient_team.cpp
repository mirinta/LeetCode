#include <string>
#include <unordered_map>
#include <vector>

/**
 * In a project, you have a list of required skills req_skills, and a list of people. The ith person
 * people[i] contains a list of skills that the person has.
 *
 * Consider a sufficient team: a set of people such that for every required skill in req_skills,
 * there is at least one person in the team who has that skill. We can represent these teams by the
 * index of each person.
 *
 * For example, team = [0, 1, 3] represents the people with skills people[0], people[1], and
 * people[3]. Return any sufficient team of the smallest possible size, represented by the index of
 * each person. You may return the answer in any order.
 *
 * It is guaranteed an answer exists.
 *
 * ! 1 <= req_skills.length <= 16
 * ! 1 <= req_skills[i].length <= 16
 * ! req_skills[i] consists of lowercase English letters.
 * ! All the strings of req_skills are unique.
 * ! 1 <= people.length <= 60
 * ! 0 <= people[i].length <= 16
 * ! 1 <= people[i][j].length <= 16
 * ! people[i][j] consists of lowercase English letters.
 * ! All the strings of people[i] are unique.
 * ! Every skill in people[i] is a skill in req_skills.
 * ! It is guaranteed a sufficient team exists.
 */

class Solution
{
public:
    std::vector<int> smallestSufficientTeam(std::vector<std::string>& req_skills,
                                            std::vector<std::vector<std::string>>& people)
    {
        const int n = req_skills.size();
        const int requiredSkills = 1 << n;
        std::unordered_map<std::string, int> map; // skill string to integer
        // e.g. skill1 = 0x1, skill2 = 0x10, skill3=0x100
        for (int i = 0; i < n; ++i) {
            map[req_skills[i]] = 1 << i;
        }
        std::vector<int> personalSkills(people.size(), 0);
        // e.g. people1 = {skill1, skill2}, skills = 0x11
        for (int i = 0; i < people.size(); ++i) {
            int skills = 0;
            for (const auto& str : people[i]) {
                if (!map.count(str))
                    continue;

                skills |= map[str];
            }
            personalSkills[i] = skills;
        }
        // 0-1 knapsack
        // dp[i] = min team size that satisfies required skills i
        std::vector<int> dp(requiredSkills, INT_MAX / 2);
        dp[0] = 0;
        std::vector<std::vector<int>> result(requiredSkills);
        for (int i = 0; i < people.size(); ++i) {
            auto copy = dp;
            for (int skills = 0; skills < (1 << n); ++skills) {
                const int newSkills = skills | personalSkills[i];
                if (copy[newSkills] > copy[skills] + 1) {
                    copy[newSkills] = copy[skills] + 1;
                    result[newSkills] = result[skills];
                    result[newSkills].push_back(i);
                }
            }
            dp = copy;
        }
        return result[(1 << n) - 1];
    }
};