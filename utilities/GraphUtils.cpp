#include "GraphUtils.h"


void GraphUtils::loadGraphFromTxt(IGraph **pGraph, IGraph::GraphStructure structure, IGraph::GraphType type) {
    std::string file_path;
    if (type == IGraph::GraphType::Directed) {
        file_path = "../input_data/directed_graph_definition.txt";
    } else {
        file_path = "../input_data/undirected_graph_definition.txt";
    }

    std::fstream file(file_path);
    if (!file.is_open()) {
        std::cout << "Error during opening the file: " << file_path << std::endl;
        return;
    }

    int nEdge, nVertex, startVertexID, endVertexID, edgeParameter;
    file >> nEdge >> nVertex;

    if (structure == IGraph::GraphStructure::IncidenceMatrix) {
        *pGraph = new MatrixGraph(type, nVertex);
    } else {
        *pGraph = new ListGraph(type, nVertex);
    }

    for (int i = 0; i < nEdge; ++i) {
        file >> startVertexID >> endVertexID >> edgeParameter;
        try {
            (*pGraph)->addEdge(startVertexID, endVertexID, edgeParameter);
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            std::cout << "Problem in " << file_path << " on line: " << i + 2 << std::endl;
        }
    }
    file.close();
}

void GraphUtils::loadRandomGraph(IGraph **pGraph, IGraph::GraphStructure structure, IGraph::GraphType type, int nVertex,
                                 double density, int parameterMin, int parameterMax) {
    density /= 100;

    if (structure == IGraph::GraphStructure::IncidenceMatrix) {
        *pGraph = new MatrixGraph(type, nVertex);
    } else {
        *pGraph = new ListGraph(type, nVertex);
    }
    IGraph *graph = *pGraph;
    int fails = 0;
    int startVertexID, endVertexID, parameter;
    while (graph->getDensity() < density) {
        try {
            startVertexID = getRand(0, graph->getVertexCount());
            endVertexID = getRand(0, graph->getVertexCount());
            parameter = getRand(parameterMin, parameterMax + 1);
            graph->addEdge(startVertexID, endVertexID, parameter);
        } catch (const std::invalid_argument &e) {
            ++fails;
        }
    }
    std::cout << "addEdge() fails: " << fails << std::endl;
}

int GraphUtils::getRand(int leftLimit, int rightLimit) {
    return leftLimit + rand() % (rightLimit - leftLimit);
}

bool GraphUtils::isGraphConnected(const IGraph *graph) {
    const IGraph *undirectedGraph = graph;

    IGraph *tmpGraph = nullptr;
    if (graph->getGraphType() == IGraph::GraphType::Directed) {
        tmpGraph = new ListGraph(IGraph::GraphType::Undirected, graph->getVertexCount());
        auto vertices = graph->getVertexes();
        DoublyLinkedList<int> successors;
        int currentVertex;
        for (auto vIt = vertices.getIterator(); vIt != vertices.getEndIt(); ++vIt) {
            currentVertex = vIt.getData();
            successors = graph->getVertexSuccessors(currentVertex);
            for (auto sIt = successors.getIterator(); sIt != successors.getEndIt(); ++sIt) {
                try {
                    tmpGraph->addEdge(currentVertex, sIt.getData(), 0);
                } catch (const std::invalid_argument &e) {
                    // Skip edge (already exists)
                }
            }
        }
        undirectedGraph = tmpGraph;
    }

    bool *isVertexVisited = new bool[undirectedGraph->getVertexCount()];
    isVertexVisited[0] = true;
    for (int i = 1; i < undirectedGraph->getVertexCount(); ++i) {
        isVertexVisited[i] = false;
    }

    Stack<int> pendingVertices;
    pendingVertices.push(0);

    int visitedVerticesCount = 0;
    int currentVertex, successor;
    DoublyLinkedList<int> currentSuccessors;
    while (!pendingVertices.isEmpty()) {
        currentVertex = pendingVertices.pop();
        ++visitedVerticesCount;
        currentSuccessors = undirectedGraph->getVertexSuccessors(currentVertex);
        for (auto it = currentSuccessors.getIterator(); it != currentSuccessors.getEndIt(); ++it) {
            successor = it.getData();
            if (isVertexVisited[successor]) {
                continue;
            }
            pendingVertices.push(successor);
            isVertexVisited[successor] = true;
        }
    }

    delete[] isVertexVisited;
    delete tmpGraph;
    return visitedVerticesCount == undirectedGraph->getVertexCount();
}
