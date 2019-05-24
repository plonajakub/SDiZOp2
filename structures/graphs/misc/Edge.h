#ifndef SDIZOP2_EDGE_H
#define SDIZOP2_EDGE_H


class Edge {
public:
    Edge() = default;

    Edge(int edgeID, int parameter) : edgeID(edgeID), parameter(parameter) {}

    bool operator==(const Edge &other) const {
        return edgeID == other.edgeID && parameter == other.parameter;
    }

    bool operator!=(const Edge &other) const {
        return edgeID != other.edgeID || parameter != other.parameter;
    }

    int edgeID;
    int parameter;
};


#endif //SDIZOP2_EDGE_H
