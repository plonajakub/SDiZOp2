#ifndef SDIZOP2_GRAPHALGORITHMS_H
#define SDIZOP2_GRAPHALGORITHMS_H

#include <limits>

#include "../structures/graphs/IGraph.h"
#include "../structures/graphs/ListGraph.h"
#include "../structures/graphs/MatrixGraph.h"
#include "../structures/Table.h"
#include "../structures/DoublyLinkedList.h"
#include "../structures/Stack.h"
#include "../structures/priority_queue/HeapPriorityQueue.h"
#include "../structures/DisjointSets.h"

class GraphAlgorithms {
public:
    static void findShortestPathDijkstra(const IGraph *graph, int startVertexID, int endVertexID,
                                         int *outPredecessorsOnPath);

    static void
    findShortestPathDijkstraHeap(const IGraph *graph, int startVertexID, int endVertexID,
                                 int *outPredecessorsOnPath, int *outShortestPathLength);

    static DoublyLinkedList<int> decodeShortestPath(const int *predecessorsOnPath, int startVertexID, int endVertexID);

    static void findShortestPathBellmanFord(const IGraph *graph, int startVertexID, int endVertexID, bool *pathExists,
                                            int *predecessorsOnPath, int *outShortestPathLength);

    // graph must be connected
    static IGraph *findMinimalSpanningTreePrim(const IGraph *graph, int *outMstTotalWeight);

    // graph must be connected
    static IGraph *findMinimalSpanningTreeKruskal(const IGraph *graph, int *outMstTotalWeight);

    static IGraph *findMaximalFlowFordFulkersonBfs(const IGraph *graph, int startVertexID, int endVertexID,
                                                   int *maxFlow);

    static IGraph *findMaximalFlowFordFulkersonDfs(const IGraph *graph, int startVertexID, int endVertexID,
                                                   int *maxFlow);

private:
    static const int INFINITY = std::numeric_limits<int>::max() / 4;

    static int getLimitedMinIdx(const int *table, const bool *isNotValid, int size);
};


#endif //SDIZOP2_GRAPHALGORITHMS_H
