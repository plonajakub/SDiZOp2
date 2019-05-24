#include "HeapPriorityQueue.h"

template<class T>
HeapPriorityQueue<T>::HeapPriorityQueue(HeapPriorityQueue::Type type) noexcept : HEAP_TYPE(type) {
}

template <class T>
void HeapPriorityQueue<T>::enqueue(const QueueNode<T> &node) {
    table.insertAtEnd(node);
    int keyIndex = table.getSize() - 1;

    // Get higher indexes for the new key until it the place meets the heap's condition
    if (HEAP_TYPE == Type::Max) {
        while (keyIndex > 0 && table[parent(keyIndex)].key < node.key) {
            table[keyIndex] = table[parent(keyIndex)];
            keyIndex = parent(keyIndex);
        }
    } else {
        while (keyIndex > 0 && table[parent(keyIndex)].key > node.key) {
            table[keyIndex] = table[parent(keyIndex)];
            keyIndex = parent(keyIndex);
        }
    }
    table[keyIndex] = node;
}

template<class T>
T HeapPriorityQueue<T>::dequeue() {
    if (table.getSize() < 1) {
        throw std::exception();
    }
    QueueNode<T> front = table[0];
    table[0] = table[table.getSize() - 1];
    table.removeFromEnd();
    this->heapify(0);
    return front.data;
}

//void HeapPriorityQueue::remove(int key) {
//    // Get key's index
//    int rmIdx = search(key);
//    if (rmIdx == KEY_NOT_FOUND) {
//        throw std::invalid_argument("Key does not exist");
//    }
//
//    // Move last value in heap into the removed key's place
//    table[rmIdx] = table[table.getSize() - 1];
//    table.removeFromEnd();
//
//    // Decide which algorithm to use in order to restore heap's order
//    if (rmIdx > 0 && rmIdx != table.getSize() && table[rmIdx] > table[parent(rmIdx)]) {
//        int movedValueIdx = rmIdx;
//
//        // Move value up in the heap
//        while (movedValueIdx > 0 && table[parent(movedValueIdx)] < table[movedValueIdx]) {
//            swap(table[movedValueIdx], table[parent(movedValueIdx)]);
//            movedValueIdx = parent(movedValueIdx);
//        }
//    } else {
//
//        // Move value down in the heap
//        heapify(rmIdx);
//    }
//
//}

//int HeapPriorityQueue::search(int key) const {
//    int keyIndex = KEY_NOT_FOUND;
//
//    // Call search algorithm
//    findKey(key, 0, keyIndex);
//    return keyIndex;
//}

//void HeapPriorityQueue::findKey(int &key, int currIdx, int &keyIndex) const {
//    // Base case
//    if (currIdx >= table.getSize() || keyIndex != KEY_NOT_FOUND) {
//        return;
//    }
//    if (table[currIdx] == key) {
//        // key found
//        keyIndex = currIdx;
//    } else if (table[currIdx] > key) {
//        // Key could be located deeper in the heap
//        findKey(key, this->right(currIdx), keyIndex);
//        findKey(key, this->left(currIdx), keyIndex);
//    }
//    // If key is greater than table[currIdx] stop looking deeper
//}

//void HeapPriorityQueue::print(const std::ostream &ostr, int index = 0, int space = 0) const {
//    // Gap between levels
//    const int COUNT = 8;
//
//    // Base case
//    if (index >= table.getSize())
//        return;
//
//    // Space for new heap's level
//    space += COUNT;
//
//    // Process right subtree first
//    print(ostr, this->right(index), space);
//
//    // Process current node
//    std::cout << std::endl;
//    for (int i = COUNT; i < space; i++)
//        std::cout << " ";
//    std::cout << table[index] << std::endl;
//
//    // Process left subtree
//    print(ostr, this->left(index), space);
//}

template <class T>
int HeapPriorityQueue<T>::parent(int index) const {
    // floor(index / 2): index from 1
    return ((index + 1) >> 1) - 1;
}

template <class T>
int HeapPriorityQueue<T>::left(int index) const {
    // 2 * index: index from 1
    return ((index + 1) << 1) - 1;
}

template <class T>
int HeapPriorityQueue<T>::right(int index) const {
    // 2 * index + 1: index from 1
    return (index + 1) << 1;
}

template <class T>
void HeapPriorityQueue<T>::heapify(int index) {
    int l = this->left(index);
    int r = this->right(index);
    int heapSize = table.getSize();

    if (this->HEAP_TYPE == Type::Max) {
        // Find the greatest node
        int largest = index;
        if (l < heapSize && table[l].key > table[largest].key) {
            largest = l;
        }
        if (r < heapSize && table[r].key > table[largest].key) {
            largest = r;
        }

        // Exchange nodes and continue
        if (largest != index) {
            this->swap(table[index], table[largest]);
            this->heapify(largest);
        }
    } else {
        // Find the greatest node
        int smallest = index;
        if (l < heapSize && table[l].key < table[smallest].key) {
            smallest = l;
        }
        if (r < heapSize && table[r].key < table[smallest].key) {
            smallest = r;
        }

        // Exchange nodes and continue
        if (smallest != index) {
            this->swap(table[index], table[smallest]);
            this->heapify(smallest);
        }
    }
}

template <class T>
void HeapPriorityQueue<T>::swap(QueueNode<T> &x, QueueNode<T> &y) const {
    QueueNode<T> temp = x;
    x = y;
    y = temp;
}

template <class T>
int HeapPriorityQueue<T>::getSize() const {
    return table.getSize();
}


//std::ostream &operator<<(std::ostream &ostr, const HeapPriorityQueue &heap) {
//    ostr << std::string(40, '$') << std::endl;
//    ostr << std::string(8, ' ') << "Right side" << std::endl << std::endl;
//    heap.print(ostr);
//    ostr << std::endl << std::string(8, ' ') << "Left side" << std::endl;
//    ostr << std::string(40, '@') << std::endl;
//    return ostr;
//}

template class HeapPriorityQueue<int>;
template class HeapPriorityQueue<Edge>;
