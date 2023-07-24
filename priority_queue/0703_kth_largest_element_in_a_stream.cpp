#include <queue>
#include <vector>

/**
 * Design a class to find the kth largest element in a stream. Note that it is the kth largest
 * element in the sorted order, not the kth distinct element.
 *
 * Implement KthLargest class:
 *
 * - KthLargest(int k, int[] nums) initializes the object with the integer k and the stream of
 * integers nums.
 *
 * - int add(int val) appends the integer val to the stream and returns the element representing the
 * kth largest element in the stream.
 *
 * ! 1 <= k
 * ! 0 <= nums.length
 * ! There will be at least k elements in the array when you search for the kth element.
 */

class KthLargest
{
public:
    KthLargest(int k, const std::vector<int>& nums) : m_k(k)
    {
        for (const auto& val : nums) {
            m_minHeap.push(val);
        }
        while (m_minHeap.size() > m_k) {
            m_minHeap.pop();
        }
    }

    int add(int val)
    {
        m_minHeap.push(val);
        if (m_minHeap.size() > m_k) {
            m_minHeap.pop();
        }
        return m_minHeap.top();
    }

private:
    int m_k;
    std::priority_queue<int, std::vector<int>, std::greater<int>> m_minHeap; // at most k elements
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
