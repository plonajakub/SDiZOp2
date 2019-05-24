#include "GraphAlgorithms.h"

DoublyLinkedList<int>
GraphAlgorithms::findShortestPathDijkStra(const IGraph *graph, int startVertexID, int endVertexID) {
    int vertexCount = graph->getVertexCount();
    bool *isVertexVisited = new bool[vertexCount];
    int *vertexDistances = new int[vertexCount];
    int *predecessorsOnPath = new int[vertexCount];

    for (int i = 0; i < vertexCount; ++i) {
        isVertexVisited[i] = false;
    }

    vertexDistances[startVertexID] = 0;
    for (int i = 0; i < vertexCount; ++i) {
        if (i == startVertexID) {
            continue;
        }
        vertexDistances[i] = std::numeric_limits<int>::max();
    }

    for (int i = 0; i < vertexCount; ++i) {
        predecessorsOnPath[i] = -1;
    }

    int currentVertexID, successorID;
    DoublyLinkedList<int> currentVertexSuccessors;
    for (int i = 0; i < vertexCount; ++i) {
        currentVertexID = GraphAlgorithms::getLimitedMinIdx(vertexDistances, isVertexVisited, vertexCount);
        if (currentVertexID == endVertexID) {
            break;
        }
        isVertexVisited[currentVertexID] = true;
        currentVertexSuccessors = graph->getVertexSuccessors(currentVertexID);
        for (DoublyLinkedList<int>::Iterator it = currentVertexSuccessors.getIterator();
             it != currentVertexSuccessors.getEndIt(); ++it) {
            successorID = it.getData();
            if (isVertexVisited[successorID]) {
                continue;
            }
            if (vertexDistances[successorID] >
                vertexDistances[currentVertexID] + graph->getEdgeParameter(currentVertexID, successorID)) {
                vertexDistances[successorID] =
                        vertexDistances[currentVertexID] + graph->getEdgeParameter(currentVertexID, successorID);
                predecessorsOnPath[successorID] = currentVertexID;
            }
        }
    }

    Stack<int> stack;
    stack.push(endVertexID);
    int vertexID = endVertexID;
    while (predecessorsOnPath[vertexID] != -1) {
        stack.push(predecessorsOnPath[vertexID]);
        vertexID = predecessorsOnPath[vertexID];
    }

    DoublyLinkedList<int> foundPath;
    while (!stack.isEmpty()) {
        foundPath.insertAtEnd(stack.pop());
    }

    delete[] isVertexVisited;
    delete[] vertexDistances;
    delete[] predecessorsOnPath;
    return foundPath;
}

int GraphAlgorithms::getLimitedMinIdx(const int *table, const bool *isNotValid, int size) {
    if (size < 1) {
        return -1;
    }
    int min = std::numeric_limits<int>::max();
    int minIdx = -1;
    for (int i = 0; i < size; ++i) {
        if (min > table[i] && !isNotValid[i]) {
            min = table[i];
            minIdx = i;
        }
    }
    return minIdx;
}

IGraph *GraphAlgorithms::findMinimalSpanningTreePrim(const IGraph *graph) {
    int vertexCount = graph->getVertexCount();
    HeapPriorityQueue<Edge> edges(HeapPriorityQueue<Edge>::Type::Min);
    IGraph *spanningTree = new ListGraph(ListGraph::GraphType::Undirected, vertexCount);
    bool *isPartOfTree = new bool[vertexCount];

    for (int i = 0; i < vertexCount; ++i) {
        isPartOfTree[i] = false;
    }

    int currentVertexID = 0;
    isPartOfTree[currentVertexID] = true;

    DoublyLinkedList<int> currentSuccessors;
    int successorID;
    int edgeWeight;
    Edge edge;
    for (int i = 0; i < vertexCount - 1; ++i) {
        currentSuccessors = graph->getVertexSuccessors(currentVertexID);
        for (DoublyLinkedList<int>::Iterator it = currentSuccessors.getIterator();
             it != currentSuccessors.getEndIt(); ++it) {
            successorID = it.getData();
            if (!isPartOfTree[successorID]) {
                edgeWeight = graph->getEdgeParameter(currentVertexID, successorID);
                edges.enqueue(QueueNode<Edge>(
                        Edge(currentVertexID, successorID, edgeWeight),
                        edgeWeight));
            }
            do {
                edge = edges.dequeue().data;
            } while (isPartOfTree[edge.endVertexID]);
            spanningTree->addEdge(edge.startVertexID, edge.endVertexID, edge.parameter);
            isPartOfTree[edge.endVertexID] = true;
            currentVertexID = edge.endVertexID;
        }
    }
    delete[] isPartOfTree;
    return spanningTree;
}
