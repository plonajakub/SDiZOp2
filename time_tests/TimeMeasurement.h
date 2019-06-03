#ifndef SDIZO_P1_TIMEMEASUREMENT_H
#define SDIZO_P1_TIMEMEASUREMENT_H


#include <iostream>
#include <fstream>
#include <exception>
#include <climits>
#include <functional>
#include <chrono>

#include "../structures/graphs/IGraph.h"
#include "../structures/graphs/MatrixGraph.h"
#include "../structures/graphs/ListGraph.h"
#include "../algorithms/GraphAlgorithms.h"
#include "../utilities/GraphUtils.h"

using std::cout;
using std::endl;

class MeasurementPoint {
public:
    int nVertex = -1;
    double time = 0;
};

class TimeMeasurement {
public:

    // Constructor
    TimeMeasurement();

    // Start time measurement
    void run();

private:

    // Number of repeated operations of the same type with the same size
    static const int DRAWS_NUMBER = 1;

    static const int ROW_NUMBER = 5;

    static const int COLUMN_NUMBER = 4;

    const std::string columnNames[4] = {
            "25%", "50%", "75%", "99%"
    };

//     SP and MST
    const int nVertexValues[ROW_NUMBER] = {50, 70, 90, 110, 130};

    // MF
//    const int nVertexValues[ROW_NUMBER] = {20, 35, 50, 65, 80};

    const int densityValues[COLUMN_NUMBER] = {25, 50, 75, 99};

    const IGraph::GraphStructure graphStructures[2] = {IGraph::GraphStructure::IncidenceMatrix,
                                                       IGraph::GraphStructure::AdjacencyList};

    const GraphUtils::Algorithm mstAlgorithms[2] = {GraphUtils::Algorithm::Kruskal, GraphUtils::Algorithm::Prim};

    const GraphUtils::Algorithm shortestPathAlgorithms[2] = {GraphUtils::Algorithm::Dijkstra,
                                                            GraphUtils::Algorithm::Bellman_Ford};

    const GraphUtils::Algorithm maxFlowAlgorithms[2] = {GraphUtils::Algorithm::Ford_Fulkerson_BFS,
                                                       GraphUtils::Algorithm::Ford_Fulkerson_DFS};

    IGraph *matrixGraph;
    IGraph *listGraph;

    MeasurementPoint **createMeasurementPointTable();

    void deleteMeasurementPointTable(MeasurementPoint **mpsTable);

    // Used to normalize accumulated times from different data draws
    void divideEachTimeByDrawsNumber(MeasurementPoint **mps);


    double countTime(const std::function<void()> &function);


    void saveTimeDataToFile(const std::string &fileName,
                            MeasurementPoint **measurementPoints);

    void analyzeMinimalSpanningTreeTime();
    void analyzeShortestPathTime();
    void analyzeMaximalFlowTime();

};


#endif //SDIZO_P1_TIMEMEASUREMENT_H
