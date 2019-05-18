#include "ListGraph.h"

ListGraph::ListGraph(ListGraph::GraphType graphType, int nVertex) : TYPE(graphType), edgeCount(0) {
    for (int i = 0; i < nVertex; ++i) {
        this->addVertex();
    }
}

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

void ListGraph::addEdge(int startVertexID, int endVertexID, int edgeParameter) {
    successorsLists[startVertexID].insertAtEnd(endVertexID);
    parametersMatrix[startVertexID][endVertexID] = edgeParameter;
    if (this->TYPE == GraphType::Undirected) {
        successorsLists[endVertexID].insertAtEnd(startVertexID);
        parametersMatrix[endVertexID][startVertexID] = edgeParameter;
    }
    ++edgeCount;
}

void ListGraph::removeEdges(int startVertexID, int endVertexID) {
    successorsLists[startVertexID].removeByValue(endVertexID);
    parametersMatrix[startVertexID][endVertexID] = std::numeric_limits<int>::max();
    if (this->TYPE == GraphType::Undirected) {
        successorsLists[endVertexID].removeByValue(startVertexID);
        parametersMatrix[endVertexID][startVertexID] = std::numeric_limits<int>::max();
    }
    --edgeCount;
}

DoublyLinkedList<int> ListGraph::getVertexSuccessors(int vertexID) const {
    return successorsLists[vertexID];
}

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

DoublyLinkedList<Edge> ListGraph::getEdgeParameters(int startVertexID, int endVertexID) const {
    DoublyLinkedList<Edge> edges;
    Edge edge(0, parametersMatrix[startVertexID][endVertexID]);
    edges.insertAtEnd(edge);
    return edges;
}

int ListGraph::getVertexCount() const {
    return successorsLists.getSize();
}

int ListGraph::getEdgeCount() const {
    return this->edgeCount;
}

double ListGraph::getDensity() const {
    int vertexCount = this->getVertexCount();
    if (vertexCount == 0) {
        return std::numeric_limits<double>::max();
    }
    return getEdgeCount() / static_cast<double>(vertexCount);
}

std::string ListGraph::toString() const {
    std::stringstream graphString;
    int vertexCount = this->getVertexCount();
    graphString << "Successors lists:" << std::endl << std::endl;
    graphString << std::setw(3) << "V" << std::endl;
    for (int i = 0; i < vertexCount; ++i) {
        graphString << std::setw(3) << i  << ": " << std::setw(2) << successorsLists[i].toString() << std::endl;
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
        for (int j = 0; j < vertexCount; ++j) {
            graphString << std::setw(4) <<
                        ((parametersMatrix[i][j] == std::numeric_limits<int>::max()) ? "*" : std::to_string(
                                parametersMatrix[i][j]))
                        << ',';
        }
        graphString << ']' << std::endl;
    }
    return graphString.str();
}

std::ostream &operator<<(std::ostream &ostr, const ListGraph &listGraph) {
    ostr << listGraph.toString();
    return ostr;
}
