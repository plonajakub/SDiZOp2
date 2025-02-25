#include "DisjointSets.h"

DisjointSets::DisjointSets(int nVertex) {
    sets = new int[nVertex];
    size = nVertex;
    for (int i = 0; i < nVertex; ++i) {
        sets[i] = i;
    }
}

DisjointSets::~DisjointSets() {
    delete[] sets;
}

int DisjointSets::getSetRepresentative(int vertexID) {
    return sets[vertexID];
}

bool DisjointSets::checkSetsDifferent(int startVertexID, int endVertexID) {
    return sets[startVertexID] != sets[endVertexID];
}

void DisjointSets::unionSets(int startVertexID, int endVertexID) {
    int startVertexIDSet = sets[startVertexID];
    int endVertexIDSet = sets[endVertexID];
    if (startVertexIDSet != endVertexIDSet) {
        for (int i = 0; i < size; ++i) {
            if (sets[i] == endVertexIDSet) {
                sets[i] = startVertexIDSet;
            }
        }
    }
}
