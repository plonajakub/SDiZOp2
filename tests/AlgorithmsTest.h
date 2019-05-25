#ifndef SDIZOP2_ALGORITHMSTEST_H
#define SDIZOP2_ALGORITHMSTEST_H

#include <iostream>

#include "../algorithms/GraphAlgorithms.h"
#include "../structures/graphs/IGraph.h"
#include "../structures/graphs/MatrixGraph.h"
#include "../structures/graphs/ListGraph.h"
#include "../utilities/GraphUtils.h"

using std::cout;
using std::endl;

class AlgorithmsTest {
public:
    void run();

private:
    void findShortestPathDijkStraTest();
    void findShortestPathBellmanFordTest();
    void findMinimalSpanningTreePrim();
    void findMinimalSpanningTreeKruskal();
};


#endif //SDIZOP2_ALGORITHMSTEST_H
