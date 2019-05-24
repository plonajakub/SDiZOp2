#ifndef SDIZOP2_HEAPPRIORITYQUEUETEST_H
#define SDIZOP2_HEAPPRIORITYQUEUETEST_H

#include <iostream>
#include <cassert>
#include "../structures/graphs/priority_queue/HeapPriorityQueue.h"

using std::cout;
using std::endl;

class HeapPriorityQueueTest {
public:
    void run();

private:
    void testEnqueue();
    void testExtractFront();
};


#endif //SDIZOP2_HEAPPRIORITYQUEUETEST_H
