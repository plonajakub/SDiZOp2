#ifndef SDIZOP2_LISTGRAPH_H
#define SDIZOP2_LISTGRAPH_H

#include <limits>
#include <iomanip>
#include <sstream>

#include "Table.h"
#include "DoublyLinkedList.h"


// Loops and multiple edges disallowed
class ListGraph {
public:

    enum GraphType {
        Directed, Undirected
    };

    ListGraph(GraphType graphType, int nVertex);

    void addEdge(int startVertexID, int endVertexID, int edgeParameter);

    void removeEdges(int startVertexID, int endVertexID);

    DoublyLinkedList<int> getVertexSuccessors(int vertexID) const;

    DoublyLinkedList<int> getVertexPredecessors(int vertexID) const;

    DoublyLinkedList<Edge> getEdgeParameters(int startVertexID, int endVertexID) const;

    int getVertexCount() const;

    int getEdgeCount() const;

    double getDensity() const;

    std::string toString() const;

private:

    void addVertex();

    const GraphType TYPE;

    Table<DoublyLinkedList<int>> successorsLists;

    // Weight or flow
    Table<Table<int>> parametersMatrix;

    int edgeCount;

    friend class ListGraphTest;
};

std::ostream &operator<<(std::ostream &ostr, const ListGraph &listGraph);

#endif //SDIZOP2_LISTGRAPH_H
