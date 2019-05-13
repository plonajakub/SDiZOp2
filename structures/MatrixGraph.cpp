#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(MatrixGraph::GraphType graphType) : TYPE(graphType) {
}

void MatrixGraph::addVertex() {
    incidenceMatrix.insertAtEnd(Table<int>());
    weightMatrix.insertAtEnd(Table<int>());
    for (int i = 0; i < weightMatrix.getSize(); ++i) {
        weightMatrix[i].insertAtEnd(std::numeric_limits<int>::max());
        weightMatrix[weightMatrix.getSize() - 1].insert(i, std::numeric_limits<int>::max());
    }
}

// TODO removeVertex()
void MatrixGraph::removeVertex(int vertexID) {

}

void MatrixGraph::addEdge(int startVertexID, int endVertexID, int weight) {
    for (int i = 0; i < incidenceMatrix.getSize(); ++i) {
        incidenceMatrix[i].insertAtEnd(0);
    }

    int lastColIdx = incidenceMatrix[0].getSize() - 1;
    incidenceMatrix[endVertexID][lastColIdx] = 1;
    if (this->TYPE == GraphType::Undirected) {
        incidenceMatrix[startVertexID][lastColIdx] = 1;
    } else {
        incidenceMatrix[startVertexID][lastColIdx] = -1;
    }

    weightMatrix[startVertexID][endVertexID] = weight;
    if (this->TYPE == GraphType::Undirected) {
        weightMatrix[endVertexID][startVertexID] = weight;
    }

}

// TODO removeEdge
void MatrixGraph::removeEdge(int startVertexID, int endVertexID) {

}

// TODO removeEdge
void MatrixGraph::removeEdge(int edgeID) {

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
        if (incidenceMatrix[vertexID][j] == -1 || (this->TYPE == GraphType::Undirected && incidenceMatrix[vertexID][j] == 1)) {
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

// TODO getEdgeWeight(int edgeID)
int MatrixGraph::getEdgeWeight(int edgeID) const {
    return 0;
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
            ((weightMatrix[i][j] == std::numeric_limits<int>::max())? "*" : std::to_string(weightMatrix[i][j]))
            << ',';
        }
        graphString << std::setw(4) << ((weightMatrix[i][this->getVertexCount() - 1] == std::numeric_limits<int>::max())? "*" : std::to_string(weightMatrix[i][this->getVertexCount() - 1])) << ']' << std::endl;
    }
    return graphString.str();
}

std::ostream &operator<<(std::ostream &ostr, const MatrixGraph &matrixGraph) {
    ostr << matrixGraph.toString();
    return ostr;
}
