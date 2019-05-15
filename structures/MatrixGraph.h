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

    class Edge {
    public:
        Edge (int edgeID, int parameter) : edgeID(edgeID), parameter(parameter) {}
        int edgeID;
        int parameter;
    };

    MatrixGraph(GraphType graphType, int nVertex);

    inline void addVertex();

//    void removeVertex(int vertexID);

    void addEdge(int startVertexID, int endVertexID, int edgeParameter);

    void removeEdges(int startVertexID, int endVertexID);

    void removeEdge(int edgeID);

    void getVertexSuccessors(int vertexID, DoublyLinkedList<int> &outSuccessorsList) const;

    void getVertexPredecessors(int vertexID, DoublyLinkedList<int> &outPredecessorsList) const;

    DoublyLinkedList<int> getEdgeIdsFromVertexes(int startVertexID, int endVertexID) const;

    // Table[0]: startVertexID
    // Table[1]: endVertexID
    Table<int> getVertexIdsFromEdge(int edgeID) const;

    inline DoublyLinkedList<Edge> getEdgeParameter(int startVertexID, int endVertexID) const;

    inline int getEdgeParameter(int edgeID) const;

    inline int getVertexCount() const;

    inline int getEdgeCount() const;

    inline double getDensity() const;

    std::string toString() const;

    static const int EDGE_NOT_PRESENT = -2;

    // TODO cannot link with static
    const int VERTEX_NOT_PRESENT = -1;

private:

    const GraphType TYPE;

    Table<Table<int>> incidenceMatrix;

    // Weight or flow
    Table<int> edgeParameters;

};

std::ostream &operator<<(std::ostream &ostr, const MatrixGraph &matrixGraph);

#endif //SDIZOP2_MATRIXGRAPH_H
