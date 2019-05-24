#ifndef SDIZOP2_QUEUENODE_H
#define SDIZOP2_QUEUENODE_H

#include "../graphs/misc/Edge.h"

template<class T>
class QueueNode {
public:
    QueueNode() = default;

    QueueNode(const T &data, int key) : data(data), key(key) {}

    bool operator==(const QueueNode<T> &other) {
        return this->data == other.data && this->key == key;
    }

    bool operator!=(const QueueNode<T> &other) {
        return this->data != other.data || this->key != key;
    }

    T data;
    int key;
};


#endif //SDIZOP2_QUEUENODE_H
