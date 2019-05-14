#ifndef SDIZOP2_MATRIXGRAPH_H
#define SDIZOP2_MATRIXGRAPH_H

#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>

#include "Table.h"
#include "DoublyLinkedList.h"

class MatrixGraph {

public:


    enum GraphType {
        Directed, Undirected
    };

    MatrixGraph(GraphType graphType, int nVertex);

    inline void addVertex();

    void removeVertex(int vertexID);

    void addEdge(int startVertexID, int endVertexID, int weight_flow);

    void removeEdge(int startVertexID, int endVertexID);

    void removeEdge(int edgeID);

    void getVertexSuccessors(int vertexID, DoublyLinkedList<int> &outSuccessorsList) const;

    void getVertexPredecessors(int vertexID, DoublyLinkedList<int> &outPredecessorsList) const;

    int getEdgeIdFromVertexes(int startVertexID, int endVertexID) const;

    // Table[0]: startVertexID
    // Table[1]: endVertexID
    Table<int> getVertexIdsFromEdge(int edgeID) const;

    int getEdgeWeight(int startVertexID, int endVertexID) const;

    int getEdgeWeight(int edgeID) const;

    int getVertexCount() const;

    int getEdgeCount() const;

    double getDensity() const;

    std::string toString() const;

    static const int EDGE_NOT_PRESENT = -2;

    // TODO cannot link with static
    const int VERTEX_NOT_PRESENT = -1;

private:

    const GraphType TYPE;

    Table<Table<int>> incidenceMatrix;

    Table<Table<int>> weightMatrix;

};

std::ostream &operator<<(std::ostream &ostr, const MatrixGraph &matrixGraph);

#endif //SDIZOP2_MATRIXGRAPH_H
