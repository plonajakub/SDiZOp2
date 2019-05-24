#include "MatrixGraph.h"

//ok
MatrixGraph::MatrixGraph(GraphType graphType, int nVertex) : TYPE(graphType) {
    if (nVertex < 1) {
        throw std::invalid_argument("ListGraph() error: graph must have at least one vertex");
    }
    for (int i = 0; i < nVertex; ++i) {
        this->addVertex();
    }
}

//ok
void MatrixGraph::addVertex() {
    incidenceMatrix.insertAtEnd(Table<int>());
    int lastVertexIdx = this->getVertexCount() - 1;
    int edgeCount = this->getEdgeCount();
    for (int i = 0; i < edgeCount; ++i) {
        incidenceMatrix[lastVertexIdx].insert(i, 0);
    }
}

//ok
void MatrixGraph::addEdge(int startVertexID, int endVertexID, int edgeParameter) {
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

//ok
void MatrixGraph::removeEdge(int startVertexID, int endVertexID) {
    if (startVertexID < 0 || startVertexID >= this->getVertexCount() || endVertexID < 0 ||
        endVertexID >= this->getVertexCount()) {
        throw std::invalid_argument("removeEdge() error: invalid vertex's index");
    }

    if (this->getEdgeParameter(startVertexID, endVertexID) == std::numeric_limits<int>::max()) {
        throw std::invalid_argument("removeEdge() error: described edge does not exist");
    }

    this->removeEdge(this->getEdgeIdFromVertexes(startVertexID, endVertexID));
}

//ok
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

//ok
DoublyLinkedList<int> MatrixGraph::getVertexSuccessors(int vertexID) const {
    DoublyLinkedList<int> outSuccessorsList;
    int edgeCount = this->getEdgeCount();
    int vertexCount = this->getVertexCount();
    for (int j = 0; j < edgeCount; ++j) {
        if (incidenceMatrix[vertexID][j] == 1) {
            for (int i = 0; i < vertexCount; ++i) {
                if (this->TYPE == GraphType::Directed) {
                    if (incidenceMatrix[i][j] == -1) {
                        outSuccessorsList.insertAtEnd(i);
                        break;
                    }
                } else {
                    if (i != vertexID && incidenceMatrix[i][j] == 1) {
                        outSuccessorsList.insertAtEnd(i);
                        break;
                    }
                }
            }
        }
    }
    return outSuccessorsList;
}

//ok
DoublyLinkedList<int> MatrixGraph::getVertexPredecessors(int vertexID) const {
    DoublyLinkedList<int> outPredecessorsList;
    int edgeCount = this->getEdgeCount();
    int vertexCount = this->getVertexCount();
    for (int j = 0; j < edgeCount; ++j) {
        if (this->TYPE == GraphType::Directed) {
            if (incidenceMatrix[vertexID][j] == -1) {
                for (int i = 0; i < vertexCount; ++i) {
                    if (incidenceMatrix[i][j] == 1) {
                        outPredecessorsList.insertAtEnd(i);
                        break;
                    }
                }
            }
        } else {
            if (incidenceMatrix[vertexID][j] == 1) {
                for (int i = 0; i < vertexCount; ++i) {
                    if (i != vertexID && incidenceMatrix[i][j] == 1) {
                        outPredecessorsList.insertAtEnd(i);
                        break;
                    }
                }
            }
        }
    }
    return outPredecessorsList;
}

//ok
int MatrixGraph::getEdgeParameter(int startVertexID, int endVertexID) const {
    int edgeID = this->getEdgeIdFromVertexes(startVertexID, endVertexID);
    if (edgeID != EDGE_NOT_PRESENT) {
        return this->edgeParameters[edgeID];
    } else {
        return std::numeric_limits<int>::max();
    }

}

//ok
int MatrixGraph::getEdgeParameter(int edgeID) const {
    return edgeParameters[edgeID];
}

//ok
int MatrixGraph::getVertexCount() const {
    return incidenceMatrix.getSize();
}

//ok
int MatrixGraph::getEdgeCount() const {
    return edgeParameters.getSize();
}

//ok
double MatrixGraph::getDensity() const {
    double edgeCount = this->getEdgeCount();
    int vertexCount = this->getVertexCount();
    if (this->TYPE == GraphType::Directed) {
        return edgeCount / (vertexCount * (vertexCount - 1));
    } else {
        return edgeCount / ((vertexCount * (vertexCount - 1)) / 2);
    }
}

//ok
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

//OK
int MatrixGraph::getEdgeIdFromVertexes(int startVertexID, int endVertexID) const {
    int edgeCount = this->getEdgeCount();
    for (int j = 0; j < edgeCount; ++j) {
        if (incidenceMatrix[startVertexID][j] == 1) {
            if (this->TYPE == GraphType::Directed) {
                if (incidenceMatrix[endVertexID][j] == -1)
                    return j;
            } else {
                if (incidenceMatrix[endVertexID][j] == 1 && endVertexID != startVertexID)
                    return j;
            }
        }
    }
    return EDGE_NOT_PRESENT;
}

//ok
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

//ok
bool MatrixGraph::isVertexPartOfEdge(int vertexID, int edgeID) const {
    return incidenceMatrix[vertexID][edgeID] != 0;
}


