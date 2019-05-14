#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(GraphType graphType, int nVertex) : TYPE(graphType) {
    for (int i = 0; i < nVertex; ++i) {
        this->addVertex();
    }
}

void MatrixGraph::addVertex() {
    incidenceMatrix.insertAtEnd(Table<int>());
    for (int i = 0; i < this->getEdgeCount(); ++i) {
        incidenceMatrix[this->getVertexCount() - 1].insert(i, 0);
    }
    weightMatrix.insertAtEnd(Table<int>());
    for (int i = 0; i < this->getVertexCount() - 1; ++i) {
        weightMatrix[this->getVertexCount() - 1].insert(i, std::numeric_limits<int>::max());
    }
    for (int i = 0; i < this->getVertexCount(); ++i) {
        weightMatrix[i].insertAtEnd(std::numeric_limits<int>::max());
    }
}

// TODO removeVertex()
void MatrixGraph::removeVertex(int vertexID) {
    throw std::exception();
}

void MatrixGraph::addEdge(int startVertexID, int endVertexID, int weight_flow) {
    for (int i = 0; i < this->getVertexCount(); ++i) {
        incidenceMatrix[i].insertAtEnd(0);
    }

    int lastEdgeIdx = this->getEdgeCount() - 1;
    incidenceMatrix[startVertexID][lastEdgeIdx] = 1;
    if (this->TYPE == GraphType::Undirected) {
        incidenceMatrix[endVertexID][lastEdgeIdx] = 1;
    } else {
        incidenceMatrix[endVertexID][lastEdgeIdx] = -1;
    }

    weightMatrix[startVertexID][endVertexID] = weight_flow;
    if (this->TYPE == GraphType::Undirected) {
        weightMatrix[endVertexID][startVertexID] = weight_flow;
    }
}

void MatrixGraph::removeEdge(int startVertexID, int endVertexID) {
    int edgeID = this->getEdgeIdFromVertexes(startVertexID, endVertexID);
    for (int i = 0; i < this->getVertexCount(); ++i) {
        incidenceMatrix[i].remove(edgeID);
    }
    weightMatrix[startVertexID][endVertexID] = std::numeric_limits<int>::max();
    if (this->TYPE == GraphType::Undirected) {
        weightMatrix[endVertexID][startVertexID] = std::numeric_limits<int>::max();
    }
}

void MatrixGraph::removeEdge(int edgeID) {
    for (int i = 0; i < this->getVertexCount(); ++i) {
        incidenceMatrix[i].remove(edgeID);
    }
    Table<int> vertexes = this->getVertexIdsFromEdge(edgeID);
    weightMatrix[vertexes[0]][vertexes[1]] = std::numeric_limits<int>::max();
    if (this->TYPE == GraphType::Undirected) {
        weightMatrix[vertexes[1]][vertexes[0]] = std::numeric_limits<int>::max();
    }
}

void MatrixGraph::getVertexSuccessors(int vertexID, DoublyLinkedList<int> &outSuccessorsList) const {
    int lastColIdx = incidenceMatrix[0].getSize() - 1;
    for (int j = 0; j < lastColIdx; ++j) {
        if (incidenceMatrix[vertexID][j] == 1) {
            for (int i = 0; i < incidenceMatrix.getSize(); ++i) {
                if (this->TYPE == GraphType::Directed && incidenceMatrix[i][j] == -1) {
                    outSuccessorsList.insertAtEnd(i);
                } else if (this->TYPE == GraphType::Undirected && i != vertexID && incidenceMatrix[i][j] == 1) {
                    outSuccessorsList.insertAtEnd(i);
                }
            }
        }
    }
}

void MatrixGraph::getVertexPredecessors(int vertexID, DoublyLinkedList<int> &outPredecessorsList) const {
    int lastColIdx = incidenceMatrix[0].getSize() - 1;
    for (int j = 0; j < lastColIdx; ++j) {
        if (incidenceMatrix[vertexID][j] == -1 ||
            (this->TYPE == GraphType::Undirected && incidenceMatrix[vertexID][j] == 1)) {
            for (int i = 0; i < incidenceMatrix.getSize(); ++i) {
                if (this->TYPE == GraphType::Directed && incidenceMatrix[i][j] == 1) {
                    outPredecessorsList.insertAtEnd(i);
                } else if (this->TYPE == GraphType::Undirected && i != vertexID && incidenceMatrix[i][j] == 1) {
                    outPredecessorsList.insertAtEnd(i);
                }
            }
        }
    }
}

int MatrixGraph::getEdgeWeight(int startVertexID, int endVertexID) const {
    return weightMatrix[startVertexID][endVertexID];
}

int MatrixGraph::getEdgeWeight(int edgeID) const {
    Table<int> vertexes = this->getVertexIdsFromEdge(edgeID);
    return weightMatrix[vertexes[0]][vertexes[1]];
}

int MatrixGraph::getVertexCount() const {
    return incidenceMatrix.getSize();
}

int MatrixGraph::getEdgeCount() const {
    return incidenceMatrix[0].getSize();
}

double MatrixGraph::getDensity() const {
    if (getVertexCount() == 0) {
        return std::numeric_limits<double>::max();
    }
    return getEdgeCount() / static_cast<double>(getVertexCount());
}

std::string MatrixGraph::toString() const {
    std::ostringstream graphString;
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
        graphString << std::setw(4) << incidenceMatrix[i][this->getEdgeCount() - 1] << ']' << std::endl;
    }

    graphString << std::endl << "Weight matrix:" << std::endl << std::endl;
    graphString << std::setw(6) << "V\\V ";
    for (int j = 0; j < this->getVertexCount(); ++j) {
        graphString << std::setw(4) << j << ',';
    }
    graphString << std::endl;
    for (int i = 0; i < this->getVertexCount(); ++i) {
        graphString << std::setw(3) << std::to_string(i) << std::setw(3) << "[";
        for (int j = 0; j < this->getVertexCount() - 1; ++j) {
            graphString << std::setw(4) <<
                        ((weightMatrix[i][j] == std::numeric_limits<int>::max()) ? "*" : std::to_string(
                                weightMatrix[i][j]))
                        << ',';
        }
        graphString << std::setw(4)
                    << ((weightMatrix[i][this->getVertexCount() - 1] == std::numeric_limits<int>::max()) ? "*"
                                                                                                         : std::to_string(
                                    weightMatrix[i][this->getVertexCount() - 1])) << ']' << std::endl;
    }
    return graphString.str();
}

int MatrixGraph::getEdgeIdFromVertexes(int startVertexID, int endVertexID) const {
    for (int j = 0; j < this->getEdgeCount(); ++j) {
        if (incidenceMatrix[startVertexID][j] == 1 &&
            ((this->TYPE == GraphType::Directed && incidenceMatrix[endVertexID][j] == -1) ||
             (this->TYPE == GraphType::Undirected && incidenceMatrix[endVertexID][j] == 1)
            )
                ) {
            return j;
        }
    }
    return EDGE_NOT_PRESENT;
}

Table<int> MatrixGraph::getVertexIdsFromEdge(int edgeID) const {
    Table<int> vertexes;
    vertexes.insertAtEnd(VERTEX_NOT_PRESENT); // startVertexID
    vertexes.insertAtEnd(VERTEX_NOT_PRESENT); // endVertexID
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

std::ostream &operator<<(std::ostream &ostr, const MatrixGraph &matrixGraph) {
    ostr << matrixGraph.toString();
    return ostr;
}
