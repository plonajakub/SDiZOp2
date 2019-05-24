#include "AlgorithmsTest.h"

#define pStartInfo(method) cout << "##### GraphUtilsTest::" << (method) << "() start #####" << endl
#define pEndInfo(method) cout << "%%%%% GraphUtilsTest::" << (method) << "() end %%%%%" << endl << endl
#define directed "--------Directed:\n"
#define undirected "--------Undirected:\n"

void AlgorithmsTest::run() {
//    pStartInfo("findShortestPathDijkStraTest");
//    findShortestPathDijkStraTest();
//    pEndInfo("findShortestPathDijkStraTest");
    pStartInfo("findMinimalSpanningTreePrim");
    findMinimalSpanningTreePrim();
    pEndInfo("findMinimalSpanningTreePrim");
}

void AlgorithmsTest::findShortestPathDijkStraTest() {
    IGraph *graph;
    DoublyLinkedList<int> shortestPath;
    int startVertexID = 1;
    int endVertexId = 7;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Directed);
    cout << *graph << endl;
    shortestPath = GraphAlgorithms::findShortestPathDijkStra(graph, startVertexID, endVertexId);
    cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (IncidenceMatrix) is: " << shortestPath << endl;
    delete graph;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Directed);
    shortestPath = GraphAlgorithms::findShortestPathDijkStra(graph, startVertexID, endVertexId);
    cout << "Shortest path from " << startVertexID << " to " << endVertexId << " (AdjacencyList) is: " << shortestPath << endl;
    delete graph;
}

void AlgorithmsTest::findMinimalSpanningTreePrim() {
    IGraph *graph;
    IGraph *minimalSpanningTree;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Undirected);
    cout << *graph << endl;
    minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreePrim(graph);
    cout << "Minimal spanning tree (IncidenceMatrix) :" << minimalSpanningTree << endl;
    delete graph;
    delete minimalSpanningTree;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Undirected);
    cout << *graph << endl;
    minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreePrim(graph);
    cout << "Minimal spanning tree (AdjacencyList) :" << minimalSpanningTree << endl;
    delete graph;
    delete minimalSpanningTree;
}
