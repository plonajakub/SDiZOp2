#ifndef SDIZOP2_LISTGRAPH_H
#define SDIZOP2_LISTGRAPH_H

#include <limits>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#include "IGraph.h"
#include "../Table.h"
#include "../DoublyLinkedList.h"


// Loops and multiple edges disallowed
class ListGraph : public IGraph {
public:

    ListGraph(GraphType graphType, int nVertex);

    void addEdge(int startVertexID, int endVertexID, int edgeParameter) override;

    void removeEdge(int startVertexID, int endVertexID) override;

    DoublyLinkedList<int> getVertexSuccessors(int vertexID) const override;

    DoublyLinkedList<int> getVertexPredecessors(int vertexID) const override;

    DoublyLinkedList<int> getVertices() const override;

    int getEdgeParameter(int startVertexID, int endVertexID) const override;

    void setEdgeParameter(int startVertexID, int endVertexID, int parameter) override;

    int getVertexCount() const override;

    int getEdgeCount() const override;

    double getDensity() const override;

    std::string toString() const override;

    GraphType getGraphType() const override;

private:

    void addVertex() override;

    const GraphType TYPE;

    Table<DoublyLinkedList<int>> successorsLists;

    // Weight or flow
    Table<Table<int>> parametersMatrix;

    int edgeCount;

    friend class ListGraphTest;
};

#endif //SDIZOP2_LISTGRAPH_H
