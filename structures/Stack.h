#ifndef SDIZOP2_STACK_H
#define SDIZOP2_STACK_H

#include "DoublyLinkedList.h"

template<class T>
class Stack {
public:
    void push(const T &item) {
        list.insertAtEnd(item);
    }

    T pop() {
        T data = list.getLast();
        list.removeFromEnd();
        return data;
    }

    int getSize() const {
        return list.getSize();
    }

    bool isEmpty() const {
        return list.getSize() == 0;
    }

private:
    DoublyLinkedList<T> list;
};


#endif //SDIZOP2_STACK_H
