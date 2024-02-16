#include <unordered_map>
#include <vector>

/**
 * Given an array of integers arr.
 *
 * We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).
 *
 * Let's define a and b as follows:
 *
 * - a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
 *
 * - b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
 *
 * Note that ^ denotes the bitwise-xor operation.
 *
 * Return the number of triplets (i, j and k) Where a == b.
 *
 * ! 1 <= arr.length <= 300
 * ! 1 <= arr[i] <= 10^8
 */

class Solution
{
public:
    int countTriplets(std::vector<int>& arr) { return approach2(arr); }

private:
    // prefix xor + hash map, TC = O(N), SC = O(N)
    int approach2(const std::vector<int>& arr)
    {
        // XOR[i] = arr[0] ^ ... ^ arr[i]
        // based on approach1:
        // let map[XOR[k]] = num of i such that XOR[k] = XOR[i]
        // valid subarrays are
        // - arr[i1+1:k], j can be [i1+2:k], num of j = k-i1-1
        // - arr[i2+1:k], j can be [i2+2:k], num of j = k-i2-1
        // ...
        // - arr[ix+1:k], j can be [ix+2:k], num of j = k-ix-1
        // thus, given k, num of triplets = x*(k-1) - (i1+...+ix)
        const int n = arr.size();
        std::unordered_map<int, std::pair<int, int>> map; // XOR[k] to {x, i1+...+ix}
        // base case: arr[0:k] is valid
        // XOR[k] = arr[0] ^ ... ^ arr[j-1] ^ arr[j] ^ ... ^ arr[k] = a ^ b = 0
        // i = -1, num of triplets = num of j = k = x*(k-1) - (-1), x = 1
        map[0] = {1, -1};
        int XOR = 0;
        int result = 0;
        for (int k = 0; k < n; ++k) {
            XOR ^= arr[k];
            if (k > 0 && map.count(XOR)) {
                result += map[XOR].first * (k - 1) - map[XOR].second;
            }
            map[XOR].first++;
            map[XOR].second += k;
        }
        return result;
    }

    // prefix xor, TC = O(N^2), SC = O(N)
    int approach1(const std::vector<int>& arr)
    {
        // let XOR[i] = arr[0] ^ arr[1] ^ ... ^ arr[i-1]
        // if j > i,
        // XOR[j] = arr[0] ^ ... ^ arr[i] ^ arr[i+1] ^ ... ^ arr[j-1]
        // XOR[j+1] ^ XOR[i] = arr[i] ^ ... ^ arr[j]
        //
        // given a pair of i and k where 0 <= i < k < n,
        // a = arr[i] ^ ... ^ arr[j-1] = XOR[j] ^ XOR[i]
        // b = arr[j] ^ ... ^ arr[k] = XOR[k + 1] ^ XOR[j]
        // if a == b, then a ^ b = XOR[i] ^ XOR[k + 1] = 0
        // j can be any value in the range of (i,k], num of j = k-i
        const int n = arr.size();
        std::vector<int> XOR(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            XOR[i] = XOR[i - 1] ^ arr[i - 1];
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int k = i + 1; k < n; ++k) {
                if ((XOR[i] ^ XOR[k + 1]) == 0) {
                    result += k - i;
                }
            }
        }
        return result;
    }
};