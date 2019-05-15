#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(GraphType graphType, int nVertex) : TYPE(graphType) {
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

// TODO removeVertex()
//void MatrixGraph::removeVertex(int vertexID) {
//    throw std::exception();
//}

void MatrixGraph::addEdge(int startVertexID, int endVertexID, int edgeParameter) {
    int vertexCount = this->getVertexCount();
    for (int i = 0; i < vertexCount; ++i) {
        incidenceMatrix[i].insertAtEnd(0);
    }

    int lastEdgeIdx = this->getEdgeCount() - 1;
    incidenceMatrix[startVertexID][lastEdgeIdx] = 1;
    if (this->TYPE == GraphType::Undirected) {
        incidenceMatrix[endVertexID][lastEdgeIdx] = 1;
    } else {
        incidenceMatrix[endVertexID][lastEdgeIdx] = -1;
    }

    edgeParameters.insertAtEnd(edgeParameter);
}

void MatrixGraph::removeEdges(int startVertexID, int endVertexID) {
    DoublyLinkedList<int> edges = this->getEdgeIdsFromVertexes(startVertexID, endVertexID);
    for (DoublyLinkedList<int>::Iterator it = edges.getIterator(); it != edges.getEndIt(); ++it) {
        this->removeEdge(it.getData());
    }
}

void MatrixGraph::removeEdge(int edgeID) {
    int vertexCount = this->getVertexCount();
    for (int i = 0; i < vertexCount; ++i) {
        incidenceMatrix[i].remove(edgeID);
    }

    edgeParameters.remove(edgeID);
}

void MatrixGraph::getVertexSuccessors(int vertexID, DoublyLinkedList<int> &outSuccessorsList) const {
    int edgeCount = this->getEdgeCount();
    int vertexCount = this->getVertexCount();
    for (int j = 0; j < edgeCount; ++j) {
        if (incidenceMatrix[vertexID][j] == 1) {
            for (int i = 0; i < vertexCount; ++i) {
                if (this->TYPE == GraphType::Directed) {
                    if (incidenceMatrix[i][j] == -1)
                        outSuccessorsList.insertAtEnd(i);
                } else {
                    if (i != vertexID && incidenceMatrix[i][j] == 1)
                        outSuccessorsList.insertAtEnd(i);
                }
            }
        }
    }
}

void MatrixGraph::getVertexPredecessors(int vertexID, DoublyLinkedList<int> &outPredecessorsList) const {
    int edgeCount = this->getEdgeCount();
    int vertexCount = this->getVertexCount();
    for (int j = 0; j < edgeCount; ++j) {
//        if (incidenceMatrix[vertexID][j] == -1) {
//            for (int i = 0; i < vertexCount; ++i) {
//                if (this->TYPE == GraphType::Directed) {
//                    if (incidenceMatrix[i][j] == -1)
//                        outSuccessorsList.insertAtEnd(i);
//                } else {
//                    if (i != vertexID && incidenceMatrix[i][j] == 1)
//                        outSuccessorsList.insertAtEnd(i);
//                }
//            }
//        }
    }
}

DoublyLinkedList<MatrixGraph::Edge> MatrixGraph::getEdgeParameter(int startVertexID, int endVertexID) const {
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

    graphString << std::endl << "Weight\\Flow table:" << std::endl << std::endl;
    graphString << std::setw(6) << "E";
    for (int j = 0; j < this->getEdgeCount(); ++j) {
        graphString << std::setw(4) << j << ',';
    }
    graphString << std::endl;
    graphString << std::setw(3) << "[";
    for (int j = 0; j < this->getEdgeCount() - 1; ++j) {
        graphString << std::setw(4) <<
                    ((edgeParameters[j] == std::numeric_limits<int>::max()) ?
                     "*" : std::to_string(edgeParameters[j]))
                    << ',';
    }
    graphString << std::setw(4)
                << ((edgeParameters[this->getEdgeCount() - 1] == std::numeric_limits<int>::max()) ?
                    "*" : std::to_string(edgeParameters[this->getEdgeCount() - 1])) << ']' << std::endl;

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
