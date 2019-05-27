#ifndef SDIZO_P1_HEAP_H
#define SDIZO_P1_HEAP_H

#include <string>
#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include <limits>

#include "QueueNode.h"
#include "../Table.h"
#include "../graphs/misc/Edge.h"
#include "../graphs/misc/DijkstraVertex.h"

template <class T>
class HeapPriorityQueue {
public:

    enum Type {
        Min, Max
    };

    explicit HeapPriorityQueue(Type type) noexcept;

    // specialized constructor for Dijkstra algorithm
    explicit HeapPriorityQueue(Type type, int nVertex, int startVertexID);

    // Inserts key into heap
    void enqueue(const QueueNode<T> &node);

    T dequeue();

    // specialized constructor for Dijkstra algorithm
    void decreaseVertexKey(int vertexID, int newDistanceFromSource);

    // specialized constructor for Dijkstra algorithm
    DijkstraVertex operator[](int vertexID) const;

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

    static const int INFINITY = std::numeric_limits<int>::max() / 4;

    // This heap is implemented as a table
    Table<QueueNode<T>> table;

    // Specialized for Dijkstra algorithm
    Table<int> vertexHeapIndex;

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
