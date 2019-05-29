#include <iostream>
#include <cstdlib>

#include "tests/MatrixGraphTest.h"
#include "tests/HeapPriorityQueueTest.h"
#include "tests/ListGraphTest.h"
#include "tests/GraphUtilsTest.h"
#include "tests/AlgorithmsTest.h"

#include "menu/ConsoleMenu.h"

using std::cout;
using std::endl;

int main() {
    srand(time(nullptr));

//    MatrixGraphTest mgt;
//    mgt.run();
//
//    HeapPriorityQueueTest hpqt;
//    hpqt.run();
//
//    ListGraphTest lgt;
//    lgt.run();
//
//    GraphUtilsTest gut;
//    gut.run();

//    AlgorithmsTest at;
//    at.run();

    ConsoleMenu cm;
    cm.start();

    return 0;
}