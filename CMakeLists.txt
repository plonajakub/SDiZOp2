cmake_minimum_required(VERSION 3.14)
project(SDiZOp2)

set(CMAKE_CXX_STANDARD 11)

add_executable(SDiZOp2 structures/DoublyLinkedList.h structures/DoublyLinkedList.cpp structures/Table.h structures/Table.cpp main.cpp structures/MatrixGraph.cpp structures/MatrixGraph.h tests/MatrixGraphTest.cpp tests/MatrixGraphTest.h)