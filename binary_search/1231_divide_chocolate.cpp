#include <vector>

/**
 * You have one chocolate bar that consists of some chunks. Each chunk has its own sweetness given
 * by the array sweetness.
 *
 * You want to share the chocolate with your k friends so you start cutting the chocolate bar into k
 * + 1 pieces using k cuts, each piece consists of some consecutive chunks.
 *
 * Being generous, you will eat the piece with the minimum total sweetness and give the other pieces
 * to your friends.
 *
 * Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.
 *
 * ! 0 <= k < sweetness.length <= 10^4
 * ! 1 <= sweetness[i] <= 10^5
 */

class Solution
{
public:
    int maximizeSweetness(std::vector<int>& sweetness, int k)
    {
        // k+1 subarrays, sum of each subarray >= x
        // we want to maximize x
        int lo = INT_MAX;
        int hi = 0;
        for (const auto& val : sweetness) {
            lo = std::min(val, lo);
            hi += val;
        }
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, sweetness, k + 1)) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

private:
    bool isValid(int minSum, const std::vector<int>& nums, int minGroups)
    {
        // minSum=7, nums=[1,2,3,4,5,6,7,8,9], minGroups=6
        // group1: 1,2,3,4
        // group2: 5,6
        // group3: 7
        // group4: 8
        // group5: 9
        // therefore, the function should return false
        int sum = 0;
        int count = 0;
        for (const auto& val : nums) {
            sum += val;
            if (sum >= minSum) {
                sum = 0;
                count++;
            }
            if (count >= minGroups)
                return true;
        }
        return false;
    }
};