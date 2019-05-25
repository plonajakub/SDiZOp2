#ifndef SDIZOP2_DISJOINTSETS_H
#define SDIZOP2_DISJOINTSETS_H

#include "graphs/misc/Edge.h"

// Disjoint sets of vertices
class DisjointSets {
public:
    explicit DisjointSets(int nVertex);

    ~DisjointSets();


    int getSetRepresentative(int vertexID);

    bool checkSetsDifferent(int startVertexID, int endVertexID);

    void unionSets(int startVertexID, int endVertexID);

private:
    int *sets;
    int size;
};


#endif //SDIZOP2_DISJOINTSETS_H
