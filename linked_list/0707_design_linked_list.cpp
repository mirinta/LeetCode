#include <memory>

/**
 * Design your implementations of the linked list. You can choose to use a singly or doubly linked
 * list.
 *
 * A node in a singly linked list should have two attributes: "val" and "next". "val" is the value
 * of the current node, and "next" is a pointer/reference to the next node. If you want to use the
 * doubly linked list, you will need one more attribute "prev" to indicate the previous node in the
 * linked list. Assume all nodes in the linked list are 0-indexed.
 *
 * Implement the "MyLinkedList" class:
 *
 * - "MyLinkedList()" initializes the "MyLinkedList" object.
 *
 * - "int get(int index)" gets the value of the "index"th node in the linked list. If the index is
 * invalid, return -1.
 *
 * - "void addAtHead(int val)" adds a node of value "val" before the first element of the linked
 * list. After the insertion, the new node will be the first node of the linked list.
 *
 * - "void addAtTail(int val)" appends a node of value "val" as the last element of the linked list.
 *
 * - "void addAtIndex(int index, int val)" adds a node of value "val" before the "index"th node in
 * the linked list. If "index" equals the length of the linked list, the node will be appended to
 * the end of the linked list. If "index" is greater than the length, the node will not be inserted.
 *
 * - "void deleteAtIndex(int index)" deletes the "index"th node in the linked list, if the index is
 * valid.
 */

class MyLinkedList
{
public:
    explicit MyLinkedList() = default;

    int get(int index) const
    {
        if (index < 0 || index >= _size)
            return -1;

        const auto* node = _vHead.next.get();
        for (int i = 0; i < index; ++i) {
            node = node->next.get();
        }
        return node->val;
    }

    void addAtHead(int val) { addAtIndex(0, val); };

    void addAtTail(int val) { addAtIndex(_size, val); }

    void addAtIndex(int index, int val)
    {
        if (index < 0 || index > _size)
            return;

        auto* prev = &_vHead;
        for (int i = 0; i < index; ++i) {
            prev = prev->next.get();
        }
        prev->next = std::make_unique<Node>(val, prev->next.release());
        _size++;
    }

    void deleteAtIndex(int index)
    {
        if (index < 0 || index >= _size)
            return;

        auto* prev = &_vHead;
        for (int i = 0; i < index; ++i) {
            prev = prev->next.get();
        }
        prev->next.reset(prev->next->next.release());
        _size--;
    }

private:
    struct Node
    {
        Node(int val, Node* next) : val(val), next(next) {}
        explicit Node() : val(0), next(nullptr) {}
        explicit Node(int val) : val(val), next(nullptr) {}

        int val;
        std::unique_ptr<Node> next;
    };
    Node _vHead{};
    int _size{0};
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
