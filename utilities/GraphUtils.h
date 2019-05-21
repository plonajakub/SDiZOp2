#ifndef SDIZOP2_GRAPHUTILS_H
#define SDIZOP2_GRAPHUTILS_H

#include <fstream>
#include <iostream>
#include <cstdlib>

#include "../structures/IGraph.h"
#include "../structures/ListGraph.h"
#include "../structures/MatrixGraph.h"

class GraphUtils {
public:

    static void loadGraphFromTxt(IGraph **pGraph, IGraph::GraphStructure structure, IGraph::GraphType type);

    // Density in %
    static void loadRandomGraph(IGraph **pGraph, IGraph::GraphStructure structure, IGraph::GraphType type, int nVertex,
                                double density, int parameterMin, int parameterMax);

private:
    // Returns random value from [leftLimit, rightLimit) interval
    static int getRand(int leftLimit, int rightLimit);

    friend class GraphUtilsTest;
};


#endif //SDIZOP2_GRAPHUTILS_H
