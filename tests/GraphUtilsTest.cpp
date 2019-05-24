#include "GraphUtilsTest.h"

#define pStartInfo(method) cout << "##### GraphUtilsTest::" << (method) << "() start #####" << endl
#define pEndInfo(method) cout << "%%%%% GraphUtilsTest::" << (method) << "() end %%%%%" << endl << endl
#define directed "--------Directed:\n"
#define undirected "--------Undirected:\n"

void GraphUtilsTest::run() {
    pStartInfo("loadGraphFromTxtTest");
    loadGraphFromTxtTest();
    pEndInfo("loadGraphFromTxtTest");
    pStartInfo("loadRandomGraphTest");
    loadRandomGraphTest();
    pEndInfo("loadRandomGraphTest");
}

void GraphUtilsTest::loadGraphFromTxtTest() {
    IGraph *graph = nullptr;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Directed);
    cout << directed << *graph << endl;
    delete graph;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Undirected);
    cout << undirected << *graph << endl;
    delete graph;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Directed);
    cout << directed << *graph << endl;
    delete graph;

    GraphUtils::loadGraphFromTxt(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Undirected);
    cout << undirected << *graph << endl;
    delete graph;
}

void GraphUtilsTest::loadRandomGraphTest() {
    IGraph *graph = nullptr;

    GraphUtils::loadRandomGraph(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Directed, 10, 50, 0,
                                100);
    cout << directed << *graph << endl;
    delete graph;

    GraphUtils::loadRandomGraph(&graph, IGraph::GraphStructure::IncidenceMatrix, IGraph::GraphType::Undirected, 10, 50,
                                0,
                                100);
    cout << undirected << *graph << endl;
    delete graph;

    GraphUtils::loadRandomGraph(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Directed, 10, 50, 0,
                                100);
    cout << directed << *graph << endl;
    delete graph;

    GraphUtils::loadRandomGraph(&graph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Undirected, 10, 50,
                                0,
                                100);
    cout << undirected << *graph << endl;
    delete graph;
}
