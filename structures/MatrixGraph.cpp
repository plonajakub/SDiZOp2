#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(MatrixGraph::GraphType graphType) : TYPE(graphType) {
}

void MatrixGraph::addVertex() {
    // TODO operator= for Table<T>
    incidenceMatrix.insertAtEnd(Table<int>());
}

void MatrixGraph::removeVertex(int vertexID) {

}

void MatrixGraph::addEdge(int startVertexID, int endVertexID, int weight) {

}

void MatrixGraph::removeEdge(int startVertexID, int endVertexID) {

}

void MatrixGraph::removeEdge(int edgeID) {

}

void MatrixGraph::getVertexSuccessors(int vertexID, DoublyLinkedList<int> &outSuccessorsList) const {

}

void MatrixGraph::getVertexPredecessors(int vertexID, DoublyLinkedList<int> &outPredecessorsList) const {

}

int MatrixGraph::getEdgeWeight(int startVertexID, int endVertexID) const {
    return 0;
}

int MatrixGraph::getEdgeWeight(int edgeID) const {
    return 0;
}

int MatrixGraph::getVertexCount() const {
    return 0;
}

int MatrixGraph::getEdgeCount() const {
    return 0;
}

int MatrixGraph::getDensity() const {
    return 0;
}

std::string MatrixGraph::toString() const {
    return std::string();
}

std::ostream &operator<<(std::ostream &ostr, const MatrixGraph &matrixGraph) {
    return <#initializer#>;
}
