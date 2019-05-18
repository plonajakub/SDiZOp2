#include "Table.h"

template <class T>
Table<T>::Table() noexcept : size(0), capacity(0), table(nullptr) {
}

template <class T>
Table<T>::~Table() noexcept {
    delete[] table;
}

template<class T>
Table<T>::Table(const Table &otherTable) : size(0), capacity(0), table(nullptr) {
    for (int i = 0; i < otherTable.getSize(); ++i) {
        this->insert(i, otherTable[i]);
    }
}

template<class T>
Table<T> &Table<T>::operator=(const Table &otherTable) {
    if (this != &otherTable) {
        while (this->getSize() > 0) {
            this->removeFromEnd();
        }
        for (int i = 0; i < otherTable.getSize(); ++i) {
            this->insert(i, otherTable[i]);
        }
    }
    return *this;
}

template <class T>
void Table<T>::insert(int index, const T &value) {
    // Check if index is valid
    if (index > size || index < 0) {
        throw std::out_of_range("insert() failed: index out of bounds");
    }
    if (capacity == 0) {
        // First elements is being inserted
        table = new T[1];
        capacity = 1;
    } else if (capacity > size) {
        // Insert element without enlarging table
        for (int i = size - 1; i >= index; --i) {
            table[i + 1] = table[i];
        }
    } else if (capacity == size) {
        // Table must be enlarged before insertion
        auto *tmpTable = new T[ENLARGEMENT_COEFFICIENT * capacity];
        int i;
        for (i = 0; i < index; ++i) {
            tmpTable[i] = table[i];
        }
        for (int j = index + 1; i < size; ++i, ++j) {
            tmpTable[j] = table[i];
        }
        delete[] table;
        table = tmpTable;
        capacity *= ENLARGEMENT_COEFFICIENT;
    }
    table[index] = value;
    ++size;
}

template <class T>
void Table<T>::insertAtStart(const T &value) {
    if (capacity == 0) {
        // First elements is being inserted
        table = new T[1];
        capacity = 1;
    } else if (capacity > size) {
        // Insert element without enlarging table
        for (int i = size - 1; i >= 0; --i) {
            table[i + 1] = table[i];
        }
    } else if (capacity == size) {
        // Table must be enlarged before insertion
        auto *tmpTable = new T[ENLARGEMENT_COEFFICIENT * capacity];
        for (int i = size - 1; i >= 0; --i) {
            tmpTable[i + 1] = table[i];
        }
        delete[] table;
        table = tmpTable;
        capacity *= ENLARGEMENT_COEFFICIENT;
    }
    table[0] = value;
    ++size;
}

template <class T>
void Table<T>::insertAtEnd(const T &value) {
    if (capacity == 0) {
        // First elements is being inserted
        table = new T[1];
        capacity = 1;
    } else if (capacity == size) {
        // Table must be enlarged before insertion
        auto *tmpTable = new T[ENLARGEMENT_COEFFICIENT * capacity];
        for (int i = 0; i < size; ++i) {
            tmpTable[i] = table[i];
        }
        delete[] table;
        table = tmpTable;
        capacity *= ENLARGEMENT_COEFFICIENT;
    }
    table[size] = value;
    ++size;
}

template <class T>
void Table<T>::remove(int index) {
    // Check if index is valid
    if (index >= size || index < 0) {
        throw std::out_of_range("remove() failed: index out of bounds");
    }
    if (size == 1) {
        // Remove last element
        delete[] table;
        table = nullptr;
        capacity = 0;
    } else if (getFullFactor() > REDUCTION_COEFFICIENT) {
        // Table doesn't have to be reduced after removal
        for (int i = index; i < size - 1; ++i) {
            table[i] = table[i + 1];
        }
    } else {
        // Table has to be reduced after removal
        auto *tmpTable = new T[capacity / ENLARGEMENT_COEFFICIENT];
        int i;
        for (i = 0; i < index; ++i) {
            tmpTable[i] = table[i];
        }
        ++i;
        for (int j = index; i < size; ++i, ++j) {
            tmpTable[j] = table[i];
        }
        delete[] table;
        table = tmpTable;
        capacity /= ENLARGEMENT_COEFFICIENT;
    }
    --size;
}

template <class T>
void Table<T>::removeFromStart() {
    // Check if table is not empty
    if (size < 1) {
        throw std::out_of_range("removeFromStart() failed: table is empty");
    }
    if (size == 1) {
        // Remove last element
        delete[] table;
        table = nullptr;
        capacity = 0;
    } else if (getFullFactor() > REDUCTION_COEFFICIENT) {
        // Table doesn't have to be reduced after removal
        for (int i = 0; i < size - 1; ++i) {
            table[i] = table[i + 1];
        }
    } else {
        // Table has to be reduced after removal
        auto *tmpTable = new T[capacity / ENLARGEMENT_COEFFICIENT];
        for (int i = 0; i < size - 1; ++i) {
            tmpTable[i] = table[i + 1];
        }
        delete[] table;
        table = tmpTable;
        capacity /= ENLARGEMENT_COEFFICIENT;
    }
    --size;
}

template <class T>
void Table<T>::removeFromEnd() {
    // Check if table is not empty
    if (size < 1) {
        throw std::out_of_range("removeFromEnd() failed: table is empty");
    }
    if (size == 1) {
        // Remove last element
        delete[] table;
        table = nullptr;
        capacity = 0;
    } else if (getFullFactor() == REDUCTION_COEFFICIENT) {
        // Table has to be reduced after removal
        auto *tmpTable = new T[capacity / ENLARGEMENT_COEFFICIENT];
        for (int i = 0; i < size - 1; ++i) {
            tmpTable[i] = table[i];
        }
        delete[] table;
        table = tmpTable;
        capacity /= ENLARGEMENT_COEFFICIENT;
    }
    --size;
}

template <class T>
int Table<T>::search(const T &value) const {
    int index = VALUE_NOT_FOUND;

    // Perform linear search on the table
    for (int i = 0; i < size; ++i) {
        if (table[i] == value) {
            index = i;
            break;
        }
    }
    return index;
}

template <class T>
std::string Table<T>::toString() const {
    std::string strTable;
    strTable.append("[");
    for (int i = 0; i < size - 1; ++i) {
        strTable.append(std::to_string(table[i]));
        strTable.append(", ");
    }
    if (size != 0) {
        strTable.append(std::to_string(table[size - 1]));
    }
    strTable.append("]");
    return strTable;
}

// TODO Table<Table<int>>::toString() to be implemented
template <>
std::string Table<Table<int>>::toString() const {
    std::string strTable;
    strTable.append("[");
    for (int i = 0; i < size - 1; ++i) {
        strTable.append("NOT IMPLEMENTED");
        strTable.append(", ");
    }
    if (size != 0) {
        strTable.append("NOT IMPLEMENTED");
    }
    strTable.append("]");
    return strTable;
}

// TODO Table<QueueNode<int>>::toString() to be implemented
template <>
std::string Table<QueueNode<int>>::toString() const {
    std::string strTable;
    strTable.append("[");
    for (int i = 0; i < size - 1; ++i) {
        strTable.append("NOT IMPLEMENTED");
        strTable.append(", ");
    }
    if (size != 0) {
        strTable.append("NOT IMPLEMENTED");
    }
    strTable.append("]");
    return strTable;
}

// TODO Table<DoublyLinkedList<int>>::toString() to be implemented
template <>
std::string Table<DoublyLinkedList<int>>::toString() const {
    std::string strTable;
    strTable.append("[");
    for (int i = 0; i < size - 1; ++i) {
        strTable.append("NOT IMPLEMENTED");
        strTable.append(", ");
    }
    if (size != 0) {
        strTable.append("NOT IMPLEMENTED");
    }
    strTable.append("]");
    return strTable;
}

template <class T>
T &Table<T>::operator[](int index) {
    if (index >= size || index < 0) {
        throw std::out_of_range("operator[]() failed: index out of bounds");
    }
    return table[index];
}

template <class T>
T &Table<T>::operator[](int index) const {
    if (index >= size || index < 0) {
        throw std::out_of_range("operator[]() failed: index out of bounds");
    }
    return table[index];
}

template <class T>
int Table<T>::getSize() const {
    return size;
}

template <class T>
int Table<T>::getCapacity() const {
    return capacity;
}

template <class T>
double Table<T>::getFullFactor() const {
    if (capacity == 0) {
        return 1;
    } else {
        return static_cast<double>(size) / capacity;
    }
}

template <class T>
bool Table<T>::operator==(const Table<T> &otherTable) const {
    if (this->getSize() != otherTable.getSize()) {
        return false;
    }
    for (int i = 0; i < this->size; ++i) {
        if ((*this)[i] != otherTable[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool Table<T>::operator!=(const Table<T> &otherTable) const {
    return !(*this == otherTable);
}

template <class T>
std::ostream &operator<<(std::ostream &ostr, const Table<T> &table) {
    ostr << table.toString();
    return ostr;
}

template class Table<int>;
template class Table<Table<int>>;
template class Table<QueueNode<int>>;
template class Table<DoublyLinkedList<int>>;
template std::ostream &operator<<(std::ostream &ostr, const Table<int> &table);