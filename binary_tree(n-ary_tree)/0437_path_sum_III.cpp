#include <unordered_map>

/**
 Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Given the root of a binary tree and an integer targetSum, return the number of paths where the
 * sum of the values along the path equals targetSum.
 *
 * The path does not need to start or end at the root or a leaf, but it must go downwards (i.e.,
 * traveling only from parent nodes to child nodes).
 *
 * ! The number of nodes in the tree is in the range [0, 1000].
 * ! -10^9 <= Node.val <= 10^9
 * ! -1000 <= targetSum <= 1000
 */

class Solution
{
public:
    int pathSum(TreeNode* root, int targetSum)
    {
        traverse(0, targetSum, root);
        return result;
    }

private:
    int result = 0;
    std::unordered_map<long, int> map; // map[i]=j, there are j paths with path sum i

    void traverse(long currentSum, int targetSum, TreeNode* node)
    {
        if (!node)
            return;

        currentSum += node->val;
        if (currentSum == targetSum) {
            result++;
        }
        if (map.count(currentSum - targetSum)) {
            result += map[currentSum - targetSum];
        }
        map[currentSum]++;
        traverse(currentSum, targetSum, node->left);
        traverse(currentSum, targetSum, node->right);
        map[currentSum]--;
    }
};