#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(GraphType graphType, int nVertex) : TYPE(graphType) {
    if (nVertex < 1) {
        throw std::invalid_argument("ListGraph() error: graph must have at least one vertex");
    }
    for (int i = 0; i < nVertex; ++i) {
        this->addVertex();
    }
}

void MatrixGraph::addVertex() {
    incidenceMatrix.insertAtEnd(Table<int>());
    int lastVertexIdx = this->getVertexCount() - 1;
    int edgeCount = this->getEdgeCount();
    for (int i = 0; i < edgeCount; ++i) {
        incidenceMatrix[lastVertexIdx].insert(i, 0);
    }
}

void MatrixGraph::addEdge(int startVertexID, int endVertexID, int edgeParameter) {
    if (startVertexID < 0 || startVertexID >= this->getVertexCount() || endVertexID < 0 ||
        endVertexID >= this->getVertexCount()) {
        throw std::invalid_argument("addEdge() error: invalid vertex's index");
    }
    if (startVertexID == endVertexID) {
        throw std::invalid_argument("addEdge() error: loops are disallowed");
    }
//    // Multiple edges are not represented in this graph's structure
//    if (this->getEdgeParameters(startVertexID, endVertexID).getIterator().getData().parameter !=
//        std::numeric_limits<int>::max()) {
//        throw std::invalid_argument("addEdge() error: multiple edges are disallowed");
//    }

    int vertexCount = this->getVertexCount();
    for (int i = 0; i < vertexCount; ++i) {
        incidenceMatrix[i].insertAtEnd(0);
    }
    edgeParameters.insertAtEnd(edgeParameter);

    int lastEdgeIdx = this->getEdgeCount() - 1;
    incidenceMatrix[startVertexID][lastEdgeIdx] = 1; // beginning of the edge
    if (this->TYPE == GraphType::Undirected) { // end of the edge
        incidenceMatrix[endVertexID][lastEdgeIdx] = 1;
    } else {
        incidenceMatrix[endVertexID][lastEdgeIdx] = -1;
    }
}

void MatrixGraph::removeEdges(int startVertexID, int endVertexID) {
    if (startVertexID < 0 || startVertexID >= this->getVertexCount() || endVertexID < 0 ||
        endVertexID >= this->getVertexCount()) {
        throw std::invalid_argument("removeEdge() error: invalid vertex's index");
    }

    DoublyLinkedList<Edge> eList = this->getEdgeParameters(startVertexID, endVertexID);
    if (eList.isEmpty()) {
        throw std::invalid_argument("removeEdge() error: described edge does not exist");
    }

    DoublyLinkedList<int> edges = this->getEdgeIdsFromVertexes(startVertexID, endVertexID);
    for (DoublyLinkedList<int>::Iterator it = edges.getIterator(); it != edges.getEndIt(); ++it) {
        this->removeEdge(it.getData());
        DoublyLinkedList<int>::Iterator eit = it;
        ++eit;
        for (; eit != edges.getEndIt(); ++eit) {
            --eit.getData();
        }
    }
}

void MatrixGraph::removeEdge(int edgeID) {
    if (edgeID < 0 || edgeID >= this->getEdgeCount()) {
        throw std::invalid_argument("removeEdge() error: invalid edgeID");
    }

    int vertexCount = this->getVertexCount();
    for (int i = 0; i < vertexCount; ++i) {
        incidenceMatrix[i].remove(edgeID);
    }

    edgeParameters.remove(edgeID);
}

DoublyLinkedList<int> MatrixGraph::getVertexSuccessors(int vertexID) const {
    DoublyLinkedList<int> outSuccessorsList;
    int edgeCount = this->getEdgeCount();
    int vertexCount = this->getVertexCount();
    for (int j = 0; j < edgeCount; ++j) {
        if (incidenceMatrix[vertexID][j] == 1) {
            for (int i = 0; i < vertexCount; ++i) {
                if (this->TYPE == GraphType::Directed) {
                    if (incidenceMatrix[i][j] == -1 && !outSuccessorsList.contains(i)) {
                        outSuccessorsList.insertAtEnd(i);
                        break;
                    }
                } else {
                    if (i != vertexID && incidenceMatrix[i][j] == 1 && !outSuccessorsList.contains(i)) {
                        outSuccessorsList.insertAtEnd(i);
                        break;
                    }
                }
            }
        }
    }
    return outSuccessorsList;
}

DoublyLinkedList<int> MatrixGraph::getVertexPredecessors(int vertexID) const {
    DoublyLinkedList<int> outPredecessorsList;
    int edgeCount = this->getEdgeCount();
    int vertexCount = this->getVertexCount();
    for (int j = 0; j < edgeCount; ++j) {
        if (this->TYPE == GraphType::Directed) {
            if (incidenceMatrix[vertexID][j] == -1) {
                for (int i = 0; i < vertexCount; ++i) {
                    if (incidenceMatrix[i][j] == 1 && !outPredecessorsList.contains(i)) {
                        outPredecessorsList.insertAtEnd(i);
                        break;
                    }
                }
            }
        } else {
            if (incidenceMatrix[vertexID][j] == 1) {
                for (int i = 0; i < vertexCount; ++i) {
                    if (i != vertexID && incidenceMatrix[i][j] == 1 && !outPredecessorsList.contains(i)) {
                        outPredecessorsList.insertAtEnd(i);
                        break;
                    }
                }
            }
        }
    }
    return outPredecessorsList;
}

DoublyLinkedList<Edge> MatrixGraph::getEdgeParameters(int startVertexID, int endVertexID) const {
    DoublyLinkedList<int> edges = this->getEdgeIdsFromVertexes(startVertexID, endVertexID);
    DoublyLinkedList<Edge> combinedEdges;
    for (DoublyLinkedList<int>::Iterator it = edges.getIterator(); it != edges.getEndIt(); ++it) {
        combinedEdges.insertAtEnd(Edge(it.getData(), edgeParameters[it.getData()]));
    }
    return combinedEdges;
}

int MatrixGraph::getEdgeParameter(int edgeID) const {
    return edgeParameters[edgeID];
}

int MatrixGraph::getVertexCount() const {
    return incidenceMatrix.getSize();
}

int MatrixGraph::getEdgeCount() const {
    return edgeParameters.getSize();
}

double MatrixGraph::getDensity() const {
    int vertexCount = this->getVertexCount();
    if (vertexCount == 0) {
        return std::numeric_limits<double>::max();
    }
    return getEdgeCount() / static_cast<double>(vertexCount);
}

std::string MatrixGraph::toString() const {
    std::ostringstream graphString;
    int lastEdgeIdx = this->getEdgeCount() - 1;
    graphString << "Incidence matrix:" << std::endl << std::endl;
    graphString << std::setw(6) << "V\\E ";
    for (int j = 0; j < this->getEdgeCount(); ++j) {
        graphString << std::setw(4) << j << ',';
    }
    graphString << std::endl;
    for (int i = 0; i < this->getVertexCount(); ++i) {
        graphString << std::setw(3) << std::to_string(i) << std::setw(3) << "[";
        for (int j = 0; j < this->getEdgeCount() - 1; ++j) {
            graphString << std::setw(4) << incidenceMatrix[i][j] << ',';
        }
        if (lastEdgeIdx >= 0) {
            graphString << std::setw(4) << incidenceMatrix[i][lastEdgeIdx];
        }
        graphString << ']' << std::endl;
    }

    graphString << std::endl << "Weight\\Flow table:" << std::endl << std::endl;
    graphString << std::setw(4) << "E" << std::string(2, ' ');
    for (int j = 0; j < this->getEdgeCount(); ++j) {
        graphString << std::setw(4) << j << ',';
    }
    graphString << std::endl;
    graphString << std::setw(6) << "[";
    for (int j = 0; j < this->getEdgeCount() - 1; ++j) {
        graphString << std::setw(4) <<
                    ((edgeParameters[j] == std::numeric_limits<int>::max()) ?
                     "*" : std::to_string(edgeParameters[j]))
                    << ',';
    }
    if (lastEdgeIdx >= 0) {
        graphString << std::setw(4)
                    << ((edgeParameters[this->getEdgeCount() - 1] == std::numeric_limits<int>::max()) ?
                        "*" : std::to_string(edgeParameters[this->getEdgeCount() - 1]));
    }
    graphString << ']' << std::endl;

    return graphString.str();
}

DoublyLinkedList<int> MatrixGraph::getEdgeIdsFromVertexes(int startVertexID, int endVertexID) const {
    DoublyLinkedList<int> edgeIds;
    int edgeCount = this->getEdgeCount();
    for (int j = 0; j < edgeCount; ++j) {
        if (incidenceMatrix[startVertexID][j] == 1) {
            if (this->TYPE == GraphType::Directed) {
                if (incidenceMatrix[endVertexID][j] == -1)
                    edgeIds.insertAtEnd(j);
            } else {
                if (incidenceMatrix[endVertexID][j] == 1 && endVertexID != startVertexID)
                    edgeIds.insertAtEnd(j);
            }
        }
    }
    return edgeIds;
}

Table<int> MatrixGraph::getVertexIdsFromEdge(int edgeID) const {
    Table<int> vertexes;
    int vertexValue = VERTEX_NOT_PRESENT;
    vertexes.insertAtEnd(vertexValue); // startVertexID
    vertexes.insertAtEnd(vertexValue); // endVertexID
    int vertexInsertIdx = 0;
    for (int i = 0; i < this->getVertexCount() &&
                    (vertexes[0] == VERTEX_NOT_PRESENT || vertexes[1] == VERTEX_NOT_PRESENT); ++i) {
        if (this->TYPE == GraphType::Directed) {
            if (incidenceMatrix[i][edgeID] == 1) {
                vertexes[0] = i;
            } else if (incidenceMatrix[i][edgeID] == -1) {
                vertexes[1] = i;
            }
        } else {
            if (incidenceMatrix[i][edgeID] == 1) {
                vertexes[vertexInsertIdx++] = i;
            }
        }
    }
    return vertexes;
}

bool MatrixGraph::isVertexPartOfEdge(int vertexID, int edgeID) const {
    return incidenceMatrix[vertexID][edgeID] != 0;
}


