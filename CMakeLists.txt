cmake_minimum_required(VERSION 3.14)
project(SDiZOp2)

set(CMAKE_CXX_STANDARD 11)

add_executable(SDiZOp2 structures/DoublyLinkedList.h structures/DoublyLinkedList.cpp structures/Table.h structures/Table.cpp main.cpp structures/MatrixGraph.cpp structures/MatrixGraph.h tests/MatrixGraphTest.cpp tests/MatrixGraphTest.h structures/Edge.cpp structures/Edge.h structures/HeapPriorityQueue.h structures/HeapPriorityQueue.cpp structures/QueueNode.cpp structures/QueueNode.h tests/HeapPriorityQueueTest.cpp tests/HeapPriorityQueueTest.h structures/ListGraph.cpp structures/ListGraph.h tests/ListGraphTest.cpp tests/ListGraphTest.h)