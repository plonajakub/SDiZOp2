#ifndef SDIZOP2_GRAPHALGORITHMS_H
#define SDIZOP2_GRAPHALGORITHMS_H

#include <limits>

#include "../structures/graphs/IGraph.h"
#include "../structures/graphs/ListGraph.h"
#include "../structures/Table.h"
#include "../structures/DoublyLinkedList.h"
#include "../structures/Stack.h"
#include "../structures/priority_queue/HeapPriorityQueue.h"

class GraphAlgorithms {
public:
    static DoublyLinkedList<int> findShortestPathDijkStra(const IGraph *graph, int startVertexID, int endVertexID);

    // graph must be connected
    static IGraph* findMinimalSpanningTreePrim(const IGraph *graph);

private:
    static int getLimitedMinIdx(const int *table, const bool *isNotValid, int size);
};


#endif //SDIZOP2_GRAPHALGORITHMS_H
