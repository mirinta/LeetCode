#include <queue>

/**
 * Given a stream of integers and a window size, calculate the moving average of all integers in the
 * sliding window.
 *
 * Implement the MovingAverage class:
 *
 * - MovingAverage(int size) Initializes the object with the size of the window size.
 *
 * - double next(int val) Returns the moving average of the last size values of the stream.
 *
 * ! 1 <= size <= 1000
 * ! -10^5 <= val <= 10^5
 * ! At most 10^4 calls will be made to next.
 */

class MovingAverage
{
public:
    explicit MovingAverage(int size) : _capacity(size) {}

    double next(int val)
    {
        if (_queue.size() == _capacity) {
            _sum -= _queue.front();
            _queue.pop();
        }
        _queue.push(val);
        _sum += val;
        return 1.0 * _sum / _queue.size();
    }

private:
    std::queue<int> _queue;
    const int _capacity;
    int _sum{0};
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
