#include "AlgorithmsTest.h"

#define pStartInfo(method) cout << "##### GraphUtilsTest::" << (method) << "() start #####" << endl
#define pEndInfo(method) cout << "%%%%% GraphUtilsTest::" << (method) << "() end %%%%%" << endl << endl
#define directed "--------Directed:\n"
#define undirected "--------Undirected:\n"

void AlgorithmsTest::run() {
    pStartInfo("findShortestPathDijkStraTest");
    findShortestPathDijkStraTest();
    pEndInfo("findShortestPathDijkStraTest");
    pStartInfo("findShortestPathBellmanFordTest");
    findShortestPathBellmanFordTest();
    pEndInfo("findShortestPathBellmanFordTest");
//    pStartInfo("findMinimalSpanningTreePrim");
//    findMinimalSpanningTreePrim();
//    pEndInfo("findMinimalSpanningTreePrim");
//    pStartInfo("findMinimalSpanningTreeKruskal");
//    findMinimalSpanningTreeKruskal();
//    pEndInfo("findMinimalSpanningTreeKruskal");
}

void AlgorithmsTest::findShortestPathDijkStraTest() {
    IGraph *graph;
    DoublyLinkedList<int> shortestPath;
    int startVertexID = 1;
    int endVertexId = 7;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Directed,
                                 "dijkstra_directed_graph.txt");
    cout << *graph << endl;
    shortestPath = GraphAlgorithms::findShortestPathDijkstra(graph, startVertexID, endVertexId);
    cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (IncidenceMatrix) is: " << shortestPath << endl;
    delete graph;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Directed,
                                 "dijkstra_directed_graph.txt");
    shortestPath = GraphAlgorithms::findShortestPathDijkstra(graph, startVertexID, endVertexId);
    cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (AdjacencyList) is: " << shortestPath << endl;
    delete graph;
}

void AlgorithmsTest::findShortestPathBellmanFordTest() {
    IGraph *graph;
    DoublyLinkedList<int> shortestPath;
    int startVertexID = 1;
    int endVertexId = 7;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Directed,
                                 "bellman_ford_directed_graph.txt");
    cout << *graph << endl;
    shortestPath = GraphAlgorithms::findShortestPathBellmanFord(graph, startVertexID, endVertexId);
    cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (IncidenceMatrix) is: " << shortestPath << endl;
    delete graph;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Directed,
                                 "bellman_ford_directed_graph.txt");
    shortestPath = GraphAlgorithms::findShortestPathBellmanFord(graph, startVertexID, endVertexId);
    cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (AdjacencyList) is: " << shortestPath << endl;
    delete graph;
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
