#include <iostream>

#include "tests/MatrixGraphTest.h"
#include "tests/HeapPriorityQueueTest.h"
#include "tests/ListGraphTest.h"

using std::cout;
using std::endl;

int main() {
//    MatrixGraphTest mgt;
//    mgt.run();

//    HeapPriorityQueueTest hpqt;
//    hpqt.run();

    ListGraphTest lgt;
    lgt.run();

    return 0;
}