#ifndef SDIZO_P1_DOUBLYLINKEDLIST_H
#define SDIZO_P1_DOUBLYLINKEDLIST_H


#include <climits>
#include <string>
#include <iostream>
#include <exception>

#include "graphs/misc/Edge.h"

// Represents single node of the list
template <class T>
class Node {
public:
    // Next node's pointer
    Node *next;

    // Previous node's pointer
    Node *prev;

    T data;

    // Sentry marker
    bool isSentry;

    // This constructor is used to create sentry node
    Node() : next(this), prev(this), isSentry(true) {}

    // Mainly used constructor for new nodes creation
    explicit Node(const T &data) : next(nullptr), prev(nullptr), data(data), isSentry(false) {}
};

template <class T>
class DoublyLinkedList {
public:

    class Iterator {
    public:
        explicit Iterator(Node<T> *node) {
            currNode = node;
        }
        void operator++() {
            currNode = currNode->next;
        }
        void operator--() {
            currNode = currNode->prev;
        }
        bool operator==(const Iterator &other) {
            return this->currNode == other.currNode;
        }
        bool operator!=(const Iterator &other) {
            return this->currNode != other.currNode;
        }
        T &getData() {
            return currNode->data;
        }
        const T &getData() const {
            return currNode->data;
        }
    private:
        Node<T> *currNode;
    };

    DoublyLinkedList() noexcept;

    ~DoublyLinkedList() noexcept;

    DoublyLinkedList(const DoublyLinkedList &otherList);

    DoublyLinkedList &operator=(const DoublyLinkedList &otherList);

    // Inserts new node with data equal to value into the place described by index
    void insert(int index, const T &value);

    // Inserts new node with data equal to value at beginning of the list
    void insertAtStart(const T &value);

    // Inserts new node with data equal to value at end of the list
    void insertAtEnd(const T &value);

    // Inserts new node with data equal to insertValue after the node described by data equal to searchValue
    // If searchValue does not exist this method inserts new node at the beginning of the list
    void insertAfterValue(const T &searchValue, const T &insertValue);

    // Removes node from place described by index
    void remove(int index);

    // Removes node from beginning of the list
    T removeFromStart();

    // Removes node from end of the list
    void removeFromEnd();

    // Removes node with data equal to value
    // If value does not exist on the list, this method has no effect
    void removeByValue(const T &value);

    // Performs linear search on the list and returns value's index
    // If value does not exist VALUE_NOT_FOUND is returned
    int search(const T &value) const;

    T getLast() const;

    bool operator==(const DoublyLinkedList<T> &otherList) const;

    bool operator!=(const DoublyLinkedList<T> &otherList) const;

    bool contains(const T &data) const;

    // Returns list's size
    int getSize() const;

    bool isEmpty() const;

    Iterator getIterator() const;

    Iterator getEndIt();

    Iterator getEndIt() const;

    // Makes list's string representation
    std::string toString() const;

    // Returned by search() if value was not found in the list
    static const int VALUE_NOT_FOUND = -1;
private:

    // Sentry's pointer
    Node<T> *sentry;

    // Number of elements in the list
    int size;

};

// Declared for convenience
template <class T>
std::ostream &operator<<(std::ostream &ostr, const DoublyLinkedList<T> &dll);


#endif //SDIZO_P1_DOUBLYLINKEDLIST_H
