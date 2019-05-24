#ifndef SDIZOP2_LISTGRAPHTEST_H
#define SDIZOP2_LISTGRAPHTEST_H


#include <cassert>
#include <iostream>

#include "../structures/graphs/ListGraph.h"

using std::cout;
using std::endl;

class ListGraphTest {
public:
    void run();

private:
    void testListGraph();
    void testAddEdge();
    void testRemoveEdges();
    void testGetVertexSuccessors();
    void testGetVertexPredecessors();
    void testGetEdgeParameters();
    void testGetVertexCount();
    void testGetEdgeCount();
    void testGetDensity();
    void testToString();
};

#endif //SDIZOP2_LISTGRAPHTEST_H
