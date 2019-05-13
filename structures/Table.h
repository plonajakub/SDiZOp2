#ifndef SDIZO_P1_TABLE_H
#define SDIZO_P1_TABLE_H

#include <iostream>
#include <exception>
#include <string>

template <class T>
class Table {

public:
    Table() noexcept;

    ~Table() noexcept;

    Table(const Table &otherTable);

    Table &operator=(const Table &otherTable);

    // Inserts value into table on place described by index
    void insert(int index, const T &value);

    // Inserts value into table at end
    void insertAtEnd(const T &value);

    // Inserts value into table at start
    void insertAtStart(const T &value);

    // Remove value described by index from table
    void remove(int index);

    // Remove value from table from start
    void removeFromStart();

    // Remove value from table from end
    void removeFromEnd();

    // Linear search for value in the table
    // Returns VALUE_NOT_FOUND if value is not in the table
    // Otherwise returns value's index
    int search(const T &value) const;

    // Table's string representation
    std::string toString() const;

    // For accessing table's elements
    T &operator[](int index);

    // For accessing table's elements
    T &operator[](int index) const;

    bool operator==(const Table<T> &otherTable) const;

    bool operator!=(const Table<T> &otherTable) const;

    int getSize() const;

    int getCapacity() const;

    // Returned by search() if value was not found
    static const int VALUE_NOT_FOUND = -1;

private:

    // Used to determine if the table should be enlarged
    static const int ENLARGEMENT_COEFFICIENT = 2;

    // Used to determine if the table should be reduced
    static constexpr double REDUCTION_COEFFICIENT = 0.25;

    // Numbers of elements in the table
    int size;

    // Numbers of possible elements to bo hold without enlarging the table
    int capacity;

    // First element's pointer
    T *table;

    // Calculates full factor (see implementation)
    double getFullFactor() const;
};

// Declared for convenience
template <class T>
std::ostream &operator<<(std::ostream &ostr, const Table<T> &table);

template class Table<int>;
template class Table<Table<int>>;

#endif //SDIZO_P1_TABLE_H
