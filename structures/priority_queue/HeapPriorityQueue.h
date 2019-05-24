#ifndef SDIZO_P1_HEAP_H
#define SDIZO_P1_HEAP_H

#include <string>
#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>

#include "QueueNode.h"
#include "../Table.h"
#include "../graphs/misc/Edge.h"

template <class T>
class HeapPriorityQueue {
public:

    enum Type {
        Min, Max
    };

    explicit HeapPriorityQueue(Type type) noexcept;

    // Inserts key into heap
    void enqueue(const QueueNode<T> &node);

    T dequeue();

//    // Removes key from heap
//    void remove(int key);

//    // Searches for key in heap and returns key's index
//    // If key does not exists search() returns KEY_NOT_FOUND
//    int search(int key) const;

//    // Draws heap in the console
//    void print(const std::ostream &ostr, int index, int indent) const;

    // Returns number of elements inside the heap
    int getSize() const;

//    // Index returned by search() if key was not found
//    static const int KEY_NOT_FOUND = -1;

private:

    // This heap is implemented as a table
    Table<QueueNode<T>> table;

    const Type HEAP_TYPE;

    // Parent node's index
    inline int parent(int index) const;

    // Left child node's index
    inline int left(int index) const;

    // Right child node's index
    inline int right(int index) const;

    // Standard algorithm for restoring heap order in node
    void heapify(int index);

    // Exchange values of two ints
    void swap(QueueNode<T> &x, QueueNode<T> &y) const;

//    // Performs a recursive search
//    void findKey(int &key, int currIdx, int &keyIndex) const;

    friend class HeapPriorityQueueTest;
};

//// Declared for convenience
//std::ostream &operator<<(std::ostream &ostr, const HeapPriorityQueue &heap);
#endif //SDIZO_P1_HEAP_H
