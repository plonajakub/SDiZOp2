#ifndef SDIZOP2_MATRIXGRAPH_H
#define SDIZOP2_MATRIXGRAPH_H


#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>

#include "Table.h"
#include "DoublyLinkedList.h"
#include "Edge.h"


class MatrixGraph {

public:

    enum GraphType {
        Directed, Undirected
    };

    MatrixGraph(GraphType graphType, int nVertex);

    void addEdge(int startVertexID, int endVertexID, int edgeParameter);

    void removeEdge(int edgeID);

    void removeEdges(int startVertexID, int endVertexID);

    DoublyLinkedList<int> getVertexSuccessors(int vertexID) const;

    DoublyLinkedList<int> getVertexPredecessors(int vertexID) const;

    DoublyLinkedList<int> getEdgeIdsFromVertexes(int startVertexID, int endVertexID) const;

    DoublyLinkedList<Edge> getEdgeParameter(int startVertexID, int endVertexID) const;

    inline int getEdgeParameter(int edgeID) const;

    // Table[0]: startVertexID
    // Table[1]: endVertexID
    Table<int> getVertexIdsFromEdge(int edgeID) const;

    inline bool isVertexPartOfEdge(int vertexID, int edgeID) const;

    inline int getVertexCount() const;

    inline int getEdgeCount() const;

    inline double getDensity() const;

    std::string toString() const;

    static const int EDGE_NOT_PRESENT = -2;

    static const int VERTEX_NOT_PRESENT = -1;

private:

    void addVertex();

    const GraphType TYPE;

    Table<Table<int>> incidenceMatrix;

    // Weight or flow
    Table<int> edgeParameters;

};

std::ostream &operator<<(std::ostream &ostr, const MatrixGraph &matrixGraph);


#endif //SDIZOP2_MATRIXGRAPH_H
