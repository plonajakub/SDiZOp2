#ifndef SDIZOP2_MATRIXGRAPHTEST_H
#define SDIZOP2_MATRIXGRAPHTEST_H

#include <cassert>
#include <iostream>

#include "../structures/MatrixGraph.h"

using std::cout;
using std::endl;

class MatrixGraphTest {
public:
    void run();

private:
    void testMatrixGraph();
    void testAddEdge();
    void testRemoveEdge();
    void testRemoveEdges();
    void testGetVertexSuccessors();
    void testGetVertexPredecessors();
    void testGetEdgeIdsFromVertexes();
    void testGetEdgeParameters();
    void testGetEdgeParameter();
    void testGetVertexIdsFromEdge();
    void testIsVertexPartOfEdge();
    void testGetVertexCount();
    void testGetEdgeCount();
    void testGetDensity();
    void testToString();
};


#endif //SDIZOP2_MATRIXGRAPHTEST_H
