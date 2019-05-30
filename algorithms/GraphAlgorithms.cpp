#include "GraphAlgorithms.h"

void
GraphAlgorithms::findShortestPathDijkstra(const IGraph *graph, int startVertexID, int endVertexID,
                                          int *outPredecessorsOnPath) {
    int vertexCount = graph->getVertexCount();

    bool *isVertexVisited = new bool[vertexCount];
    int *vertexDistances = new int[vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        isVertexVisited[i] = false;
        vertexDistances[i] = INFINITY;
        outPredecessorsOnPath[i] = -1;
    }
    vertexDistances[startVertexID] = 0;

    int currentVertexID, successorID, edgeWeight;
    DoublyLinkedList<int> currentVertexSuccessors;
    for (int i = 0; i < vertexCount; ++i) {
        currentVertexID = GraphAlgorithms::getLimitedMinIdx(vertexDistances, isVertexVisited, vertexCount);
        if (currentVertexID == endVertexID) {
            break;
        }
        isVertexVisited[currentVertexID] = true;
        currentVertexSuccessors = graph->getVertexSuccessors(currentVertexID);
        for (auto it = currentVertexSuccessors.getIterator(); it != currentVertexSuccessors.getEndIt(); ++it) {
            successorID = it.getData();
            if (!isVertexVisited[successorID]) {
                edgeWeight = graph->getEdgeParameter(currentVertexID, successorID);
                if (vertexDistances[successorID] > vertexDistances[currentVertexID] + edgeWeight) {
                    vertexDistances[successorID] = vertexDistances[currentVertexID] + edgeWeight;
                    outPredecessorsOnPath[successorID] = currentVertexID;
                }
            }
        }
    }
    delete[] isVertexVisited;
    delete[] vertexDistances;
}

void
GraphAlgorithms::findShortestPathDijkstraHeap(const IGraph *graph, int startVertexID, int endVertexID,
                                              int *outPredecessorsOnPath, int *outShortestPathLength) {
    int vertexCount = graph->getVertexCount();

    HeapPriorityQueue<DijkstraVertex> queue(HeapPriorityQueue<DijkstraVertex>::Type::Min, vertexCount, startVertexID);

    bool *isVertexVisited = new bool[vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        isVertexVisited[i] = false;
        outPredecessorsOnPath[i] = -1;
    }

    DijkstraVertex currentVertex;
    int successorID, edgeWeight;
    DoublyLinkedList<int> currentVertexSuccessors;
    for (int i = 0; i < vertexCount; ++i) {
        currentVertex = queue.dequeue();
        if (currentVertex.id == endVertexID) {
            *outShortestPathLength = currentVertex.distanceFromSource;
            break;
        }
        isVertexVisited[currentVertex.id] = true;
        currentVertexSuccessors = graph->getVertexSuccessors(currentVertex.id);
        for (auto it = currentVertexSuccessors.getIterator(); it != currentVertexSuccessors.getEndIt(); ++it) {
            successorID = it.getData();
            if (!isVertexVisited[successorID]) {
                edgeWeight = graph->getEdgeParameter(currentVertex.id, successorID);
                if (queue[successorID].distanceFromSource > currentVertex.distanceFromSource + edgeWeight) {
                    queue.decreaseVertexKey(successorID, currentVertex.distanceFromSource + edgeWeight);
                    outPredecessorsOnPath[successorID] = currentVertex.id;
                }
            }
        }
    }
    delete[] isVertexVisited;
}

DoublyLinkedList<int>
GraphAlgorithms::decodeShortestPath(const int *predecessorsOnPath, int startVertexID, int endVertexID) {
    Stack<int> stack;
    stack.push(endVertexID);
    int vertexID = endVertexID;
    while (predecessorsOnPath[vertexID] != -1) {
        stack.push(predecessorsOnPath[vertexID]);
        vertexID = predecessorsOnPath[vertexID];
    }

    DoublyLinkedList<int> foundPath;
    int firstVertex = stack.pop();
    if (firstVertex == startVertexID) {
        foundPath.insertAtEnd(firstVertex);
        while (!stack.isEmpty()) {
            foundPath.insertAtEnd(stack.pop());
        }
    } else {
        foundPath.insertAtEnd(-1);
    }
    return foundPath;
}

void
GraphAlgorithms::findShortestPathBellmanFord(const IGraph *graph, int startVertexID, int endVertexID, bool *pathExists,
                                             int *predecessorsOnPath, int *outShortestPathLength) {
    int vertexCount = graph->getVertexCount();

    int *vertexDistances = new int[vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        vertexDistances[i] = INFINITY;
        predecessorsOnPath[i] = -1;
    }
    vertexDistances[startVertexID] = 0;

    auto vertices = graph->getVertices();
    DoublyLinkedList<int> successors;
    int currentVertexID, successorID, edgeWeight;
    for (int i = 0; i < vertexCount - 1; ++i) {
        *pathExists = true;
        for (auto vIt = vertices.getIterator(); vIt != vertices.getEndIt(); ++vIt) {
            currentVertexID = vIt.getData();
            successors = graph->getVertexSuccessors(currentVertexID);
            for (auto sIt = successors.getIterator(); sIt != successors.getEndIt(); ++sIt) {
                successorID = sIt.getData();
                edgeWeight = graph->getEdgeParameter(currentVertexID, successorID);
                if (vertexDistances[successorID] > vertexDistances[currentVertexID] + edgeWeight) {
                    vertexDistances[successorID] = vertexDistances[currentVertexID] + edgeWeight;
                    predecessorsOnPath[successorID] = currentVertexID;
                    *pathExists = false;
                }
            }
        }
        if (*pathExists) {
            goto finish;
        }
    }
    for (auto vIt = vertices.getIterator(); vIt != vertices.getEndIt(); ++vIt) {
        currentVertexID = vIt.getData();
        successors = graph->getVertexSuccessors(currentVertexID);
        for (auto sIt = successors.getIterator(); sIt != successors.getEndIt(); ++sIt) {
            successorID = sIt.getData();
            if (vertexDistances[successorID] >
                vertexDistances[currentVertexID] + graph->getEdgeParameter(currentVertexID, successorID)) {
                *pathExists = false;
                goto finish;
            }
        }
    }
    *pathExists = true;

    finish:
    *outShortestPathLength = vertexDistances[endVertexID];
    delete[] vertexDistances;
}

int GraphAlgorithms::getLimitedMinIdx(const int *table, const bool *isNotValid, int size) {
    if (size < 1) {
        return -1;
    }
    int min = INFINITY;
    int minIdx = -1;
    for (int i = 0; i < size; ++i) {
        if (min > table[i] && !isNotValid[i]) {
            min = table[i];
            minIdx = i;
        }
    }
    return minIdx;
}

IGraph *GraphAlgorithms::findMinimalSpanningTreePrim(const IGraph *graph, int *outMstTotalWeight) {
    int vertexCount = graph->getVertexCount();
    int mstTotalWeight = 0;
    HeapPriorityQueue<Edge> edges(HeapPriorityQueue<Edge>::Type::Min);
    IGraph *spanningTree;
    switch (graph->getGraphStructure()) {
        case IGraph::IncidenceMatrix:
            spanningTree = new MatrixGraph(ListGraph::GraphType::Undirected, vertexCount);
            break;
        case IGraph::AdjacencyList:
            spanningTree = new ListGraph(ListGraph::GraphType::Undirected, vertexCount);
            break;
    }
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
        for (auto it = currentSuccessors.getIterator(); it != currentSuccessors.getEndIt(); ++it) {
            successorID = it.getData();
            if (!isPartOfTree[successorID]) {
                edgeWeight = graph->getEdgeParameter(currentVertexID, successorID);
                edges.enqueue(QueueNode<Edge>(
                        Edge(currentVertexID, successorID, edgeWeight),
                        edgeWeight));
            }
        }
        do {
            edge = edges.dequeue();
        } while (isPartOfTree[edge.endVertexID]);
        spanningTree->addEdge(edge.startVertexID, edge.endVertexID, edge.parameter);
        mstTotalWeight += edge.parameter;
        isPartOfTree[edge.endVertexID] = true;
        currentVertexID = edge.endVertexID;
    }
    *outMstTotalWeight = mstTotalWeight;
    delete[] isPartOfTree;
    return spanningTree;
}

IGraph *GraphAlgorithms::findMinimalSpanningTreeKruskal(const IGraph *graph, int *outMstTotalWeight) {
    int vertexCount = graph->getVertexCount();
    int mstTotalWieght = 0;
    DisjointSets vertexSets(vertexCount);
    HeapPriorityQueue<Edge> edges(HeapPriorityQueue<Edge>::Type::Min);
    IGraph *tree;
    switch (graph->getGraphStructure()) {
        case IGraph::IncidenceMatrix:
            tree = new MatrixGraph(IGraph::GraphType::Undirected, vertexCount);
            break;
        case IGraph::AdjacencyList:
            tree = new ListGraph(IGraph::GraphType::Undirected, vertexCount);
            break;
    }

    auto vertices = graph->getVertices();
    DoublyLinkedList<int> successors;
    int edgeWeight;
    for (auto vIt = vertices.getIterator(); vIt != vertices.getEndIt(); ++vIt) {
        successors = graph->getVertexSuccessors(vIt.getData());
        for (auto sIt = successors.getIterator(); sIt != successors.getEndIt(); ++sIt) {
            edgeWeight = graph->getEdgeParameter(vIt.getData(), sIt.getData());
            edges.enqueue(QueueNode<Edge>(
                    Edge(vIt.getData(), sIt.getData(), edgeWeight),
                    edgeWeight));
        }
    }

    Edge currentEdge;
    for (int i = 1; i < vertexCount; ++i) {
        do {
            currentEdge = edges.dequeue();
        } while (!vertexSets.checkSetsDifferent(currentEdge.startVertexID, currentEdge.endVertexID));
        tree->addEdge(currentEdge.startVertexID, currentEdge.endVertexID, currentEdge.parameter);
        mstTotalWieght += currentEdge.parameter;
        vertexSets.unionSets(currentEdge.startVertexID, currentEdge.endVertexID);
    }
    *outMstTotalWeight = mstTotalWieght;
    return tree;
}

IGraph *GraphAlgorithms::findMaximalFlowFordFulkersonBfs(const IGraph *graph, int startVertexID, int endVertexID,
                                                         int *maxFlow) {
    int graphVertexCount = graph->getVertexCount();
    *maxFlow = 0;
    IGraph *flowGraph;
    switch (graph->getGraphStructure()) {
        case IGraph::IncidenceMatrix:
            flowGraph = new MatrixGraph(ListGraph::GraphType::Directed, graphVertexCount);
            break;
        case IGraph::AdjacencyList:
            flowGraph = new ListGraph(ListGraph::GraphType::Directed, graphVertexCount);
            break;
    }

    auto graphVertices = graph->getVertices();
    DoublyLinkedList<int> successors;
    for (auto vIt = graphVertices.getIterator(); vIt != graphVertices.getEndIt(); ++vIt) {
        successors = graph->getVertexSuccessors(vIt.getData());
        for (auto sIt = successors.getIterator(); sIt != successors.getEndIt(); ++sIt) {
            flowGraph->addEdge(vIt.getData(), sIt.getData(), 0);
        }
    }
    int *bfsPredecessorsOnPath = new int[graphVertexCount];
    int *augmentingPathFlow = new int[graphVertexCount];
    DoublyLinkedList<int> *bfsVertexQueue = nullptr;
    int currentVertex, currentSuccessor = -1, currentResidualCapacity;
    bool augmentingPathFound;
    while (true) {
        for (int i = 0; i < graphVertexCount; ++i) {
            bfsPredecessorsOnPath[i] = -1;
        }
        bfsPredecessorsOnPath[startVertexID] = -2;
        augmentingPathFlow[startVertexID] = INFINITY;
        augmentingPathFound = false;
        delete bfsVertexQueue;
        bfsVertexQueue = new DoublyLinkedList<int>;
        bfsVertexQueue->insertAtEnd(startVertexID);
        while (!bfsVertexQueue->isEmpty() && !augmentingPathFound) {
            currentVertex = bfsVertexQueue->removeFromStart();
            successors = graph->getVertexSuccessors(currentVertex);
            for (auto sIt = successors.getIterator(); sIt != successors.getEndIt(); ++sIt) {
                currentSuccessor = sIt.getData();
                currentResidualCapacity = graph->getEdgeParameter(currentVertex, currentSuccessor) -
                                          flowGraph->getEdgeParameter(currentVertex, currentSuccessor);
                if (currentResidualCapacity != 0 && bfsPredecessorsOnPath[currentSuccessor] == -1) {
                    bfsPredecessorsOnPath[currentSuccessor] = currentVertex;
                    augmentingPathFlow[currentSuccessor] = ((currentResidualCapacity <
                                                             augmentingPathFlow[currentVertex])
                                                            ? currentResidualCapacity
                                                            : augmentingPathFlow[currentVertex]);
                    if (currentSuccessor == endVertexID) {
                        augmentingPathFound = true;
                        break;
                    }
                    bfsVertexQueue->insertAtEnd(currentSuccessor);
                }
            }
        }
        if (augmentingPathFound) {
            *maxFlow = *maxFlow + augmentingPathFlow[endVertexID];
            while (currentSuccessor != startVertexID) {
                currentVertex = bfsPredecessorsOnPath[currentSuccessor];
                flowGraph->setEdgeParameter(currentVertex, currentSuccessor,
                                            flowGraph->getEdgeParameter(currentVertex, currentSuccessor) +
                                            augmentingPathFlow[endVertexID]);
                currentSuccessor = currentVertex;
            }
            continue;
        }
        break;
    }
    delete[] bfsPredecessorsOnPath;
    delete[] augmentingPathFlow;
    return flowGraph;
}

IGraph *GraphAlgorithms::findMaximalFlowFordFulkersonDfs(const IGraph *graph, int startVertexID, int endVertexID,
                                                         int *maxFlow) {
    int graphVertexCount = graph->getVertexCount();
    *maxFlow = 0;
    IGraph *flowGraph;
    switch (graph->getGraphStructure()) {
        case IGraph::IncidenceMatrix:
            flowGraph = new MatrixGraph(ListGraph::GraphType::Directed, graphVertexCount);
            break;
        case IGraph::AdjacencyList:
            flowGraph = new ListGraph(ListGraph::GraphType::Directed, graphVertexCount);
            break;
    }
    auto graphVertices = graph->getVertices();
    DoublyLinkedList<int> successors;
    for (auto vIt = graphVertices.getIterator(); vIt != graphVertices.getEndIt(); ++vIt) {
        successors = graph->getVertexSuccessors(vIt.getData());
        for (auto sIt = successors.getIterator(); sIt != successors.getEndIt(); ++sIt) {
            flowGraph->addEdge(vIt.getData(), sIt.getData(), 0);
        }
    }
    int *bfsPredecessorsOnPath = new int[graphVertexCount];
    int *augmentingPathFlow = new int[graphVertexCount];
    Stack<int> *dfsVertexStack = nullptr;
    int currentVertex, currentSuccessor = -1, currentResidualCapacity;
    bool augmentingPathFound;
    while (true) {
        for (int i = 0; i < graphVertexCount; ++i) {
            bfsPredecessorsOnPath[i] = -1;
        }
        bfsPredecessorsOnPath[startVertexID] = -2;
        augmentingPathFlow[startVertexID] = INFINITY;
        augmentingPathFound = false;
        delete dfsVertexStack;
        dfsVertexStack = new Stack<int>;
        dfsVertexStack->push(startVertexID);
        while (!dfsVertexStack->isEmpty() && !augmentingPathFound) {
            currentVertex = dfsVertexStack->pop();
            successors = graph->getVertexSuccessors(currentVertex);
            for (auto sIt = successors.getIterator(); sIt != successors.getEndIt(); ++sIt) {
                currentSuccessor = sIt.getData();
                currentResidualCapacity = graph->getEdgeParameter(currentVertex, currentSuccessor) -
                                          flowGraph->getEdgeParameter(currentVertex, currentSuccessor);
                if (currentResidualCapacity != 0 && bfsPredecessorsOnPath[currentSuccessor] == -1) {
                    bfsPredecessorsOnPath[currentSuccessor] = currentVertex;
                    augmentingPathFlow[currentSuccessor] = ((currentResidualCapacity <
                                                             augmentingPathFlow[currentVertex])
                                                            ? currentResidualCapacity
                                                            : augmentingPathFlow[currentVertex]);
                    if (currentSuccessor == endVertexID) {
                        augmentingPathFound = true;
                        break;
                    }
                    dfsVertexStack->push(currentSuccessor);
                }
            }
        }
        if (augmentingPathFound) {
            *maxFlow = *maxFlow + augmentingPathFlow[endVertexID];
            while (currentSuccessor != startVertexID) {
                currentVertex = bfsPredecessorsOnPath[currentSuccessor];
                flowGraph->setEdgeParameter(currentVertex, currentSuccessor,
                                            flowGraph->getEdgeParameter(currentVertex, currentSuccessor) +
                                            augmentingPathFlow[endVertexID]);
                currentSuccessor = currentVertex;
            }
            continue;
        }
        break;
    }
    delete[] bfsPredecessorsOnPath;
    delete[] augmentingPathFlow;
    return flowGraph;
}
