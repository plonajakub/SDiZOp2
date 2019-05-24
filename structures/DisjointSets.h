#ifndef SDIZOP2_DISJOINTSETS_H
#define SDIZOP2_DISJOINTSETS_H

#include "graphs/misc/Edge.h"

template<class T>
class DSNode {
public:
    DSNode() = default;

    DSNode(const T &up, int rank) : parent(up), rank(rank) {}

    T parent;
    int rank;
};

template<class T>
class DisjointSets {
private:
    DSNode<T> *sets;
public:
    explicit DisjointSets(int dataCount) {
        sets = new DSNode<T>[dataCount];
    }

    ~DisjointSets() {
        delete[] sets;
    }

    void makeSet(int vertexID) {
        sets[vertexID].parent = vertexID;
        sets[vertexID].rank = 0;
    }

    int findSet(int vertexID) {
        if (sets[vertexID].parent != vertexID)
            sets[vertexID].parent = findSet(sets[vertexID].parent);
        return sets[vertexID].parent;
    }

    void unionSets(Edge edge) {
        int startVertexRoot, endVertexRoot;

        startVertexRoot = findSet(edge.startVertexID);
        endVertexRoot = findSet(edge.endVertexID);
        if (startVertexRoot != endVertexRoot) {
            if (sets[startVertexRoot].rank > sets[endVertexRoot].rank)
                sets[endVertexRoot].parent = startVertexRoot;
            else {
                sets[startVertexRoot].parent = endVertexRoot;
                if (sets[startVertexRoot].rank == sets[endVertexRoot].rank)
                    ++sets[endVertexRoot].rank;
            }
        }
    }
};


#endif //SDIZOP2_DISJOINTSETS_H
