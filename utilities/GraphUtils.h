#ifndef SDIZOP2_GRAPHUTILS_H
#define SDIZOP2_GRAPHUTILS_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

#include "../structures/graphs/IGraph.h"
#include "../structures/graphs/ListGraph.h"
#include "../structures/graphs/MatrixGraph.h"
#include "../structures/Stack.h"


class GraphUtils {
public:

    enum Algorithm {
        Dijkstra, Bellman_Ford, Kruskal, Prim, Ford_Fulkerson_BFS, Ford_Fulkerson_DFS
    };

    static void loadGraphFromTxt(IGraph **pGraph, IGraph::GraphStructure structure, IGraph::GraphType type,
                                 const std::string &fileName);

    // Density in %
    static void loadRandomGraph(IGraph **pGraph, IGraph::GraphStructure structure, IGraph::GraphType type, int nVertex,
                                double densityInPercents, int parameterMin, int parameterMax);

    static void loadRandomGraphWithConstraints(IGraph **pGraph, GraphUtils::Algorithm algorithm,
                                               IGraph::GraphStructure structure, int nVertex, double densityInPercents);

    static bool isGraphConnected(const IGraph *graph);

    // Returns random value from [leftLimit, rightLimit) interval
    static int getRand(int leftLimit, int rightLimit);
private:

    friend class GraphUtilsTest;
};


#endif //SDIZOP2_GRAPHUTILS_H
