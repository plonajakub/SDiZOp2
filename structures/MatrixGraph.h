#ifndef SDIZOP2_MATRIXGRAPH_H
#define SDIZOP2_MATRIXGRAPH_H

#include <iostream>

#include "Table.h"
#include "DoublyLinkedList.h"

class MatrixGraph {
public:

    enum GraphType {
        Directed, Undirected
    };

    explicit MatrixGraph(GraphType graphType);

    void addVertex();

    void removeVertex(int vertexID);

    void addEdge(int startVertexID, int endVertexID, int weight);

    void removeEdge(int startVertexID, int endVertexID);

    void removeEdge(int edgeID);

    void getVertexSuccessors(int vertexID, DoublyLinkedList<int> &outSuccessorsList) const;

    void getVertexPredecessors(int vertexID, DoublyLinkedList<int> &outPredecessorsList) const;

    int getEdgeWeight(int startVertexID, int endVertexID) const;

    int getEdgeWeight(int edgeID) const;

    int getVertexCount() const;

    int getEdgeCount() const;

    int getDensity() const;

    std::string toString() const;

private:

    const GraphType TYPE;

    Table<Table<int>> incidenceMatrix;

    Table<Table<int>> weightMatrix;

};

std::ostream &operator<<(std::ostream &ostr, const MatrixGraph &matrixGraph);

#endif //SDIZOP2_MATRIXGRAPH_H
