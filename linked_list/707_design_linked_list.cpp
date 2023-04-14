#include <memory>

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
    size_t _size{0};
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
