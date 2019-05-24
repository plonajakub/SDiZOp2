#include "ListGraph.h"

//ok
ListGraph::ListGraph(ListGraph::GraphType graphType, int nVertex) : TYPE(graphType), edgeCount(0) {
    if (nVertex < 1) {
        throw std::invalid_argument("ListGraph() error: graph must have at least one vertex");
    }
    for (int i = 0; i < nVertex; ++i) {
        this->addVertex();
    }
}

//ok
void ListGraph::addVertex() {
    successorsLists.insertAtEnd(DoublyLinkedList<int>());

    parametersMatrix.insertAtEnd(Table<int>());
    int vertexCount = this->getVertexCount();
    int lastVertexIdx = vertexCount - 1;
    for (int i = 0; i < vertexCount - 1; ++i) {
        parametersMatrix[lastVertexIdx].insertAtEnd(std::numeric_limits<int>::max());
    }
    for (int i = 0; i < vertexCount; ++i) {
        parametersMatrix[i].insertAtEnd(std::numeric_limits<int>::max());
    }
}

//ok
void ListGraph::addEdge(int startVertexID, int endVertexID, int edgeParameter) {
    if (startVertexID < 0 || startVertexID >= this->getVertexCount() || endVertexID < 0 ||
        endVertexID >= this->getVertexCount()) {
        throw std::invalid_argument("addEdge() error: invalid vertex's index");
    }
    if (startVertexID == endVertexID) {
        throw std::invalid_argument("addEdge() error: loops are disallowed");
    }
    // Multiple edges are not represented in this graph's structure
    if (this->getEdgeParameter(startVertexID, endVertexID) != std::numeric_limits<int>::max()) {
        throw std::invalid_argument("addEdge() error: multiple edges are disallowed");
    }

    successorsLists[startVertexID].insertAtEnd(endVertexID);
    parametersMatrix[startVertexID][endVertexID] = edgeParameter;
    if (this->TYPE == GraphType::Undirected) {
        successorsLists[endVertexID].insertAtEnd(startVertexID);
        parametersMatrix[endVertexID][startVertexID] = edgeParameter;
    }
    ++edgeCount;
}

//ok
void ListGraph::removeEdge(int startVertexID, int endVertexID) {
    if (startVertexID < 0 || startVertexID >= this->getVertexCount() || endVertexID < 0 ||
        endVertexID >= this->getVertexCount()) {
        throw std::invalid_argument("removeEdge() error: wrong vertex's index");
    }
    if (this->getEdgeParameter(startVertexID, endVertexID) == std::numeric_limits<int>::max()) {
        throw std::invalid_argument("addEdge() error: described edge does not exist");
    }

    successorsLists[startVertexID].removeByValue(endVertexID);
    parametersMatrix[startVertexID][endVertexID] = std::numeric_limits<int>::max();
    if (this->TYPE == GraphType::Undirected) {
        successorsLists[endVertexID].removeByValue(startVertexID);
        parametersMatrix[endVertexID][startVertexID] = std::numeric_limits<int>::max();
    }
    --edgeCount;
}

//ok
DoublyLinkedList<int> ListGraph::getVertexSuccessors(int vertexID) const {
    return successorsLists[vertexID];
}

//ok
DoublyLinkedList<int> ListGraph::getVertexPredecessors(int vertexID) const {
    if (this->TYPE == GraphType::Directed) {
        DoublyLinkedList<int> predecessors;
        int vertexCount = this->getVertexCount();
        for (int i = 0; i < vertexCount; ++i) {
            if (successorsLists[i].contains(vertexID)) {
                predecessors.insertAtEnd(i);
            }
        }
        return predecessors;
    } else {
        return successorsLists[vertexID];
    }
}

//ok
int ListGraph::getEdgeParameter(int startVertexID, int endVertexID) const {
    return parametersMatrix[startVertexID][endVertexID];
}

//ok
int ListGraph::getVertexCount() const {
    return successorsLists.getSize();
}

//ok
int ListGraph::getEdgeCount() const {
    return edgeCount;
}

//ok
double ListGraph::getDensity() const {
    int vertexCount = this->getVertexCount();
    if (this->TYPE == GraphType::Directed) {
        return static_cast<double>(edgeCount) / (vertexCount * (vertexCount - 1));
    } else {
        return static_cast<double>(edgeCount) / ((vertexCount * (vertexCount - 1)) / 2);
    }
}


std::string ListGraph::toString() const {
    std::stringstream graphString;
    int vertexCount = this->getVertexCount();
    graphString << "Successors lists:" << std::endl << std::endl;
    graphString << std::setw(3) << "V" << std::endl;
    for (int i = 0; i < vertexCount; ++i) {
        graphString << std::setw(3) << i << ": " << std::setw(2) << successorsLists[i].toString() << std::endl;
    }
    graphString << std::endl;

    graphString << "Parameter matrix:" << std::endl << std::endl;
    graphString << std::setw(5) << "V\\V" << std::setw(1) << "";
    for (int j = 0; j < vertexCount; ++j) {
        graphString << std::setw(4) << j << ',';
    }
    graphString << std::endl;
    for (int i = 0; i < vertexCount; ++i) {
        graphString << std::setw(3) << std::to_string(i) << std::setw(3) << "[";
        for (int j = 0; j < vertexCount - 1; ++j) {
            graphString << std::setw(4) <<
                        ((parametersMatrix[i][j] == std::numeric_limits<int>::max()) ? "*" : std::to_string(
                                parametersMatrix[i][j]))
                        << ',';
        }
        graphString << std::setw(4) <<
                    ((parametersMatrix[i][vertexCount - 1] == std::numeric_limits<int>::max()) ? "*" : std::to_string(
                            parametersMatrix[i][vertexCount - 1]));
        graphString << ']' << std::endl;
    }
    return graphString.str();
}
