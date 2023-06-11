#include <algorithm>
#include <vector>

/**
 * Implement a SnapshotArray that supports the following interface:
 *
 * - SnapshotArray(int length) initializes an array-like data structure with the given length.
 * Initially, each element equals 0.
 *
 * - void set(index, val) sets the element at the given index to be equal to val.
 *
 * - int snap() takes a snapshot of the array and returns the snap_id: the total number of times we
 * called snap() minus 1.
 *
 * - int get(index, snap_id) returns the value at the given index, at the time we took the snapshot
 * with the given snap_id
 *
 * ! 1 <= length <= 5 * 10^4
 * ! 0 <= index < length
 * ! 0 <= val <= 10^9
 * ! 0 <= snap_id < (the total number of times we call snap())
 * ! At most 5 * 10^4 calls will be made to set, snap, and get.
 */

class SnapshotArray
{
public:
    SnapshotArray(int length) : _snapID(0)
    {
        _snaps.resize(length);
        for (size_t i = 0; i < length; ++i) {
            _snaps[i].push_back({0, 0});
        }
    }

    void set(int index, int val) { _snaps[index].push_back({_snapID, val}); }

    int snap() { return _snapID++; }

    int get(int index, int snap_id)
    {
        auto iter = std::upper_bound(_snaps[index].begin(), _snaps[index].end(),
                                     std::make_pair(snap_id, INT_MAX));
        return std::prev(iter)->second;
    }

private:
    int _snapID;
    std::vector<std::vector<std::pair<int, int>>> _snaps;
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */