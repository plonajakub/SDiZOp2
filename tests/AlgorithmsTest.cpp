#include "AlgorithmsTest.h"

#define pStartInfo(method) cout << "##### GraphUtilsTest::" << (method) << "() start #####" << endl
#define pEndInfo(method) cout << "%%%%% GraphUtilsTest::" << (method) << "() end %%%%%" << endl << endl
#define directed "--------Directed:\n"
#define undirected "--------Undirected:\n"

void AlgorithmsTest::run() {
//    pStartInfo("findShortestPathDijkstraTest");
//    findShortestPathDijkstraTest();
//    pEndInfo("findShortestPathDijkstraTest");
//    pStartInfo("findShortestPathDijkstraHeapTest");
//    findShortestPathDijkstraHeapTest();
//    pEndInfo("findShortestPathDijkstraHeapTest");
//    pStartInfo("findShortestPathBellmanFordTest");
//    findShortestPathBellmanFordTest();
//    pEndInfo("findShortestPathBellmanFordTest");
//    pStartInfo("findMinimalSpanningTreePrim");
//    findMinimalSpanningTreePrim();
//    pEndInfo("findMinimalSpanningTreePrim");
//    pStartInfo("findMinimalSpanningTreeKruskal");
//    findMinimalSpanningTreeKruskal();
//    pEndInfo("findMinimalSpanningTreeKruskal");
//    pStartInfo("findMaximalFlowFordFulkersonBfsTest");
//    findMaximalFlowFordFulkersonBfsTest();
//    pEndInfo("findMaximalFlowFordFulkersonBfsTest");
    pStartInfo("findMaximalFlowFordFulkersonDfsTest");
    findMaximalFlowFordFulkersonDfsTest();
    pEndInfo("findMaximalFlowFordFulkersonDfsTest");
}

void AlgorithmsTest::findShortestPathDijkstraTest() {
    IGraph *graph = nullptr;
    int *predecessorsOnPath = nullptr;
    DoublyLinkedList<int> shortestPath;
    int startVertexID = 0;
    int endVertexId = 3;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Directed,
                                 "dijkstra_directed_graph.txt");
    predecessorsOnPath = new int[graph->getVertexCount()];
    cout << *graph << endl;
    GraphAlgorithms::findShortestPathDijkstra(graph, startVertexID, endVertexId, predecessorsOnPath);
    shortestPath = GraphAlgorithms::decodeShortestPath(predecessorsOnPath, endVertexId);
    cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (IncidenceMatrix) is: " << shortestPath
         << endl;
    delete graph;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Directed,
                                 "dijkstra_directed_graph.txt");
    GraphAlgorithms::findShortestPathDijkstra(graph, startVertexID, endVertexId, predecessorsOnPath);
    shortestPath = GraphAlgorithms::decodeShortestPath(predecessorsOnPath, endVertexId);
    cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (AdjacencyList) is: " << shortestPath
         << endl;
    delete graph;
    delete predecessorsOnPath;
}

void AlgorithmsTest::findShortestPathDijkstraHeapTest() {
    IGraph *graph = nullptr;
    int *predecessorsOnPath = nullptr;
    DoublyLinkedList<int> shortestPath;
    int startVertexID = 0;
    int endVertexId = 3;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Directed,
                                 "dijkstra_directed_graph.txt");
    predecessorsOnPath = new int[graph->getVertexCount()];
    cout << *graph << endl;
    GraphAlgorithms::findShortestPathDijkstraHeap(graph, startVertexID, endVertexId, predecessorsOnPath);
    shortestPath = GraphAlgorithms::decodeShortestPath(predecessorsOnPath, endVertexId);
    cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (IncidenceMatrix) is: " << shortestPath
         << endl;
    delete graph;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Directed,
                                 "dijkstra_directed_graph.txt");
    GraphAlgorithms::findShortestPathDijkstraHeap(graph, startVertexID, endVertexId, predecessorsOnPath);
    shortestPath = GraphAlgorithms::decodeShortestPath(predecessorsOnPath, endVertexId);
    cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (AdjacencyList) is: " << shortestPath
         << endl;
    delete graph;
    delete predecessorsOnPath;
}

void AlgorithmsTest::findShortestPathBellmanFordTest() {
    IGraph *graph = nullptr;
    int *predecessorsOnPath = nullptr;
    bool pathExists;
    DoublyLinkedList<int> shortestPath;
    int startVertexID = 0;
    int endVertexId = 5;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Directed,
                                 "bellman_ford_directed_graph.txt");
    predecessorsOnPath = new int[graph->getVertexCount()];
    cout << *graph << endl;
    GraphAlgorithms::findShortestPathBellmanFord(graph, startVertexID, &pathExists, predecessorsOnPath);
    if (pathExists) {
        shortestPath = GraphAlgorithms::decodeShortestPath(predecessorsOnPath, endVertexId);
        cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (IncidenceMatrix) is: "
             << shortestPath << endl;
    } else {
        cout << "Shortest path from " << startVertexID << " to " << endVertexId << " does not exist!" << endl;
    }
    delete graph;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Directed,
                                 "bellman_ford_directed_graph.txt");
    GraphAlgorithms::findShortestPathBellmanFord(graph, startVertexID, &pathExists, predecessorsOnPath);
    if (pathExists) {
        shortestPath = GraphAlgorithms::decodeShortestPath(predecessorsOnPath, endVertexId);
        cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (AdjacencyList) is: "
             << shortestPath << endl;
    } else {
        cout << "Shortest path from " << startVertexID << " to " << endVertexId << " does not exist!" << endl;
    }
    delete graph;
    delete predecessorsOnPath;
}

void AlgorithmsTest::findMinimalSpanningTreePrim() {
    IGraph *graph;
    IGraph *minimalSpanningTree;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Undirected,
                                 "prim_undirected_graph.txt");
    cout << *graph << endl;
    minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreePrim(graph);
    cout << "Minimal spanning tree (IncidenceMatrix)\n" << *minimalSpanningTree << endl;
    delete graph;
    delete minimalSpanningTree;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Undirected,
                                 "prim_undirected_graph.txt");
    cout << *graph << endl;
    minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreePrim(graph);
    cout << "Minimal spanning tree (AdjacencyList)\n" << *minimalSpanningTree << endl;
    delete graph;
    delete minimalSpanningTree;
}

void AlgorithmsTest::findMinimalSpanningTreeKruskal() {
    IGraph *graph;
    IGraph *minimalSpanningTree;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Undirected,
                                 "kruskal_undirected_graph.txt");
    cout << *graph << endl;
    minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreeKruskal(graph);
    cout << "Minimal spanning tree (IncidenceMatrix)\n" << *minimalSpanningTree << endl;
    delete graph;
    delete minimalSpanningTree;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Undirected,
                                 "kruskal_undirected_graph.txt");
    cout << *graph << endl;
    minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreeKruskal(graph);
    cout << "Minimal spanning tree (AdjacencyList)\n" << *minimalSpanningTree << endl;
    delete graph;
    delete minimalSpanningTree;
}

void AlgorithmsTest::findMaximalFlowFordFulkersonBfsTest() {
    IGraph *capacityNetwork;
    IGraph *flowNetwork;
    int maxFlow;
    int startVertexID = 2;
    int endVertexId = 4;

    GraphUtils::loadGraphFromTxt(&capacityNetwork, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Directed,
                                 "ford_fulkerson_flow_network.txt");
    cout << "Capacity network (IncidenceMatrix)\n" << *capacityNetwork << endl;
    flowNetwork = GraphAlgorithms::findMaximalFlowFordFulkersonBfs(capacityNetwork, startVertexID, endVertexId,
                                                                   &maxFlow);
    cout << "Flow network\n" << *flowNetwork << endl;
    cout << "Max flow = " << maxFlow << endl;
    delete capacityNetwork;
    delete flowNetwork;

    GraphUtils::loadGraphFromTxt(&capacityNetwork, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Directed,
                                 "ford_fulkerson_flow_network.txt");
    cout << "Capacity network (AdjacencyList)\n" << *capacityNetwork << endl;
    flowNetwork = GraphAlgorithms::findMaximalFlowFordFulkersonBfs(capacityNetwork, startVertexID, endVertexId,
                                                                   &maxFlow);
    cout << "Flow network\n" << *flowNetwork << endl;
    cout << "Max flow = " << maxFlow << endl;
    delete capacityNetwork;
    delete flowNetwork;
}

void AlgorithmsTest::findMaximalFlowFordFulkersonDfsTest() {
    IGraph *capacityNetwork;
    IGraph *flowNetwork;
    int maxFlow;
    int startVertexID = 2;
    int endVertexId = 4;

    GraphUtils::loadGraphFromTxt(&capacityNetwork, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Directed,
                                 "ford_fulkerson_flow_network.txt");
    cout << "Capacity network (IncidenceMatrix)\n" << *capacityNetwork << endl;
    flowNetwork = GraphAlgorithms::findMaximalFlowFordFulkersonDfs(capacityNetwork, startVertexID, endVertexId,
                                                                   &maxFlow);
    cout << "Flow network\n" << *flowNetwork << endl;
    cout << "Max flow = " << maxFlow << endl;
    delete capacityNetwork;
    delete flowNetwork;

    GraphUtils::loadGraphFromTxt(&capacityNetwork, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Directed,
                                 "ford_fulkerson_flow_network.txt");
    cout << "Capacity network (AdjacencyList)\n" << *capacityNetwork << endl;
    flowNetwork = GraphAlgorithms::findMaximalFlowFordFulkersonDfs(capacityNetwork, startVertexID, endVertexId,
                                                                   &maxFlow);
    cout << "Flow network\n" << *flowNetwork << endl;
    cout << "Max flow = " << maxFlow << endl;
    delete capacityNetwork;
    delete flowNetwork;
}
