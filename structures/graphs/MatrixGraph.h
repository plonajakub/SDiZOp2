#ifndef SDIZOP2_MATRIXGRAPH_H
#define SDIZOP2_MATRIXGRAPH_H


#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "IGraph.h"
#include "../Table.h"
#include "../DoublyLinkedList.h"
#include "misc/Edge.h"


class MatrixGraph : public IGraph {
public:

    MatrixGraph(GraphType graphType, int nVertex);

    void addEdge(int startVertexID, int endVertexID, int edgeParameter) override;

    void removeEdge(int edgeID);

    void removeEdge(int startVertexID, int endVertexID) override;

    DoublyLinkedList<int> getVertices() const override;

    DoublyLinkedList<int> getVertexSuccessors(int vertexID) const override;

    DoublyLinkedList<int> getVertexPredecessors(int vertexID) const override;

    int getEdgeParameter(int startVertexID, int endVertexID) const override;

    void setEdgeParameter(int startVertexID, int endVertexID, int parameter) override;

    int getEdgeParameter(int edgeID) const;

    // Table[0]: startVertexID
    // Table[1]: endVertexID
    Table<int> getVertexIdsFromEdge(int edgeID) const;

    // Returned list is sorted
    int getEdgeIdFromVertexes(int startVertexID, int endVertexID) const;

    bool isVertexPartOfEdge(int vertexID, int edgeID) const;

    int getVertexCount() const override;

    int getEdgeCount() const override;

    double getDensity() const override;

    std::string toString() const override;

    GraphType getGraphType() const override;

    static const int EDGE_NOT_PRESENT = -2;

    static const int VERTEX_NOT_PRESENT = -1;

private:

    void addVertex() override;

    const GraphType TYPE;

    Table<Table<int>> incidenceMatrix;

    // Weight or flow
    Table<int> edgeParameters;

    friend class MatrixGraphTest;
};


#endif //SDIZOP2_MATRIXGRAPH_H
