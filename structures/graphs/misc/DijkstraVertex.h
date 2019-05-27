#ifndef SDIZOP2_DIJKSTRAVERTEX_H
#define SDIZOP2_DIJKSTRAVERTEX_H


class DijkstraVertex {
public:
    DijkstraVertex() = default;

    DijkstraVertex(int id, int positionInHeap, int distanceFromSource) : id(id),
                                                                         distanceFromSource(distanceFromSource) {
    }

    bool operator==(const DijkstraVertex &other) const {
        return id == other.id &&
               distanceFromSource == other.distanceFromSource;
    }

    bool operator!=(const DijkstraVertex &other) const {
        return id != other.id ||
               distanceFromSource != other.distanceFromSource;
    }

    int id;
    int distanceFromSource;
};


#endif //SDIZOP2_DIJKSTRAVERTEX_H
