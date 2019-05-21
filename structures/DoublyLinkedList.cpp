#include "DoublyLinkedList.h"

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() noexcept {
    sentry = new Node<T>();
    size = 0;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() noexcept {
    // Free memory
    auto *it = sentry->next;
    while (!it->isSentry) {
        it = it->next;
        delete it->prev;
    }
    delete sentry;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList &otherList) {
    sentry = new Node<T>();
    size = 0;
    DoublyLinkedList<T>::Iterator otherIt = otherList.getIterator();
    DoublyLinkedList<T>::Iterator otherItEnd = otherList.getEndIt();
    while (otherIt != otherItEnd) {
        this->insertAtEnd(otherIt.getData());
        ++otherIt;
    }
}

template<class T>
DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(const DoublyLinkedList &otherList) {
    if (this != &otherList) {
        while (this->size > 0) {
            this->removeFromEnd();
        }
        DoublyLinkedList<T>::Iterator otherIt = otherList.getIterator();
        DoublyLinkedList<T>::Iterator otherItEnd = otherList.getEndIt();
        while (otherIt != otherItEnd) {
            this->insertAtEnd(otherIt.getData());
            ++otherIt;
        }
    }
    return *this;
}

template <class T>
void DoublyLinkedList<T>::insert(int index, const T &value) {
    // Check if index is valid
    if (index < 0 || index > size) {
        throw std::out_of_range("insert() failed: index out of bounds");
    }

    auto *newNode = new Node<T>(value);
    auto *it = sentry->next;

    // Find proper place for the node based on index
    for (int i = 0; i != index; ++i) {
        it = it->next;
    }

    // Insert the new node into the list
    newNode->prev = it->prev;
    it->prev->next = newNode;
    it->prev = newNode;
    newNode->next = it;
    ++size;
}

template <class T>
void DoublyLinkedList<T>::insertAtStart(const T &value) {
    auto *newNode = new Node<T>(value);

    // Insert the new node into the list
    newNode->next = sentry->next;
    sentry->next->prev = newNode;
    sentry->next = newNode;
    newNode->prev = sentry;
    ++size;
}

template <class T>
void DoublyLinkedList<T>::insertAtEnd(const T &value) {
    auto *newNode = new Node<T>(value);

    // Insert the new node into the list
    newNode->prev = sentry->prev;
    sentry->prev->next = newNode;
    sentry->prev = newNode;
    newNode->next = sentry;
    ++size;
}

template <class T>
void DoublyLinkedList<T>::insertAfterValue(const T &searchValue, const T &insertValue) {
    // Find proper place for a new node based on searchValue
    for (auto *it = sentry->next; !it->isSentry; it = it->next) {
        if (it->data == searchValue) {
            // searchValue found -> insert the new node
            auto *newNode = new Node<T>(insertValue);
            newNode->next = it->next;
            it->next->prev = newNode;
            it->next = newNode;
            newNode->prev = it;
            ++size;
            return;
        }
    }
    // searchValue not found -> insert the new node at beginning of the list
    this->insertAtStart(insertValue);
}

template <class T>
void DoublyLinkedList<T>::remove(int index) {
    // Check if index is valid
    if (index < 0 || index >= size) {
        throw std::out_of_range("remove() failed: index out of bounds");
    }

    // Find a node to be deleted
    Node<T> *it = sentry->next;
    for (int i = 0; i != index; ++i) {
        it = it->next;
    }

    // Delete the node
    it->prev->next = it->next;
    it->next->prev = it->prev;
    delete it;
    --size;
}

template <class T>
void DoublyLinkedList<T>::removeFromStart() {
    // Check if list is empty
    if (size == 0) {
        throw std::out_of_range("removeFromStart() failed: list is empty");
    }

    // Remove the node at start of the list
    auto *head = sentry->next;
    sentry->next = head->next;
    head->next->prev = sentry;
    delete head;
    --size;
}

template <class T>
void DoublyLinkedList<T>::removeFromEnd() {
    // Check if list is empty
    if (size == 0) {
        throw std::out_of_range("removeFromEnd() failed: list is empty");
    }

    // Remove the node at end of the list
    auto *tail = sentry->prev;
    sentry->prev = tail->prev;
    tail->prev->next = sentry;
    delete tail;
    --size;
}

template <class T>
void DoublyLinkedList<T>::removeByValue(const T &value) {
    try {
        this->remove(this->search(value));
    } catch (std::out_of_range &e) {
        // No action: value does not exist in the list
    }
}

template <class T>
int DoublyLinkedList<T>::search(const T &value) const {
    int returnIdx = VALUE_NOT_FOUND;
    int currentIdx = 0;
    Node<T> *it = sentry->next;

    // Perform linear search
    while (!it->isSentry) {
        if (it->data == value) {
            returnIdx = currentIdx;
            break;
        }
        ++currentIdx;
        it = it->next;
    }
    return returnIdx;
}

template <class T>
std::string DoublyLinkedList<T>::toString() const {
    std::string strDll;
    strDll.append("[");
    Node<T> *it = sentry->next;
    while (!it->next->isSentry) {
        strDll.append(std::to_string(it->data));
        strDll.append(", ");
        it = it->next;
    }
    if (size != 0) {
        strDll.append(std::to_string(it->data));
    }
    strDll.append("]");
    return strDll;
}

// TODO DoublyLinkedList<DoublyLinkedList<int>>::toString() to be implemented
template <>
std::string DoublyLinkedList<DoublyLinkedList<int>>::toString() const {
    std::string strDll;
    strDll.append("[");
    Node<DoublyLinkedList<int>> *it = sentry->next;
    while (!it->next->isSentry) {
        strDll.append("NOT IMPLEMENTED");
        strDll.append(", ");
        it = it->next;
    }
    if (size != 0) {
        strDll.append("NOT IMPLEMENTED");
    }
    strDll.append("]");
    return strDll;
}

// TODO DoublyLinkedList<Edge>::toString() to be implemented
template  <>
std::string DoublyLinkedList<Edge>::toString() const {
    std::string strDll;
    strDll.append("[");
    Node<Edge> *it = sentry->next;
    while (!it->next->isSentry) {
        strDll.append("NOT IMPLEMENTED");
        strDll.append(", ");
        it = it->next;
    }
    if (size != 0) {
        strDll.append("NOT IMPLEMENTED");
    }
    strDll.append("]");
    return strDll;
}

template <class T>
int DoublyLinkedList<T>::getSize() const {
    return size;
}

template <class T>
bool DoublyLinkedList<T>::operator==(const DoublyLinkedList<T> &otherList) const {
    if (this->size != otherList.getSize()) {
        return false;
    }
    DoublyLinkedList<T>::Iterator it = this->getIterator();
    DoublyLinkedList<T>::Iterator itEnd = this->getEndIt();
    DoublyLinkedList<T>::Iterator otherIt = otherList.getIterator();
    while (it != itEnd) {
        if (it.getData() != otherIt.getData()) {
            return false;
        }
        ++it;
        ++otherIt;
    }
    return true;
}

template <class T>
bool DoublyLinkedList<T>::operator!=(const DoublyLinkedList<T> &otherList) const {
    return !(*this == otherList);
}

template <class T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::getIterator() const {
    return typename DoublyLinkedList<T>::Iterator(this->sentry->next);
}

template<class T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::getEndIt() {
    return DoublyLinkedList::Iterator(this->sentry);
}

template<class T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::getEndIt() const {
    return DoublyLinkedList::Iterator(this->sentry);
}

template<class T>
bool DoublyLinkedList<T>::contains(const T &data) const {
    for (Iterator it = this->getIterator(); it != this->getEndIt(); ++it) {
        if (it.getData() == data) {
            return true;
        }
    }
    return false;
}

template<class T>
bool DoublyLinkedList<T>::isEmpty() const {
    return size == 0;
}

template <class T>
std::ostream &operator<<(std::ostream &ostr, const DoublyLinkedList<T> &dll) {
    ostr << dll.toString();
    return ostr;
}

template class DoublyLinkedList<int>;
template class DoublyLinkedList<DoublyLinkedList<int>>;
template class DoublyLinkedList<Edge>;
template std::ostream &operator<<(std::ostream &ostr, const DoublyLinkedList<int> &table);