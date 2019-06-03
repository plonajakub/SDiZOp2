#include "TimeMeasurement.h"

TimeMeasurement::TimeMeasurement() : listGraph(nullptr), matrixGraph(nullptr) {
}

void TimeMeasurement::run() {
    analyzeMinimalSpanningTreeTime();
//    analyzeShortestPathTime();
//    analyzeMaximalFlowTime();
}

double TimeMeasurement::countTime(const std::function<void()> &function) {
    std::chrono::high_resolution_clock::time_point start, finish;
    std::chrono::duration<double, std::milli> elapsed;
    start = std::chrono::high_resolution_clock::now();
    function();
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    return elapsed.count();
}

void
TimeMeasurement::saveTimeDataToFile(const std::string &fileName, MeasurementPoint **measurementPoints) {
    const char sep = ',';
    std::ofstream file("../time_tests/data/" + fileName, std::ofstream::trunc);
    if (!file.is_open()) {
        throw std::ios_base::failure(fileName + " not opened!");
    }

    cout << "Writing file " + fileName + "...";
    file << "Wierzcho\u0142ki \\ G\u0119sto\u015b\u0107";
    for (const auto &columnName : columnNames) {
        file << sep << columnName;
    }
    file << endl;

    for (int i = 0; i < ROW_NUMBER; ++i) {
        for (int j = 0; j < COLUMN_NUMBER - 1; ++j) {
            if (measurementPoints[i][j].nVertex != measurementPoints[i][j + 1].nVertex) {
                throw std::exception();
            }
        }
        file << measurementPoints[i][0].nVertex;
        for (int j = 0; j < COLUMN_NUMBER; ++j) {
            file << sep << static_cast<int>(measurementPoints[i][j].time);
        }
        file << endl;
    }
    cout << "written!" << endl;
    file.close();
}

MeasurementPoint **TimeMeasurement::createMeasurementPointTable() {
    auto **mpsTable = new MeasurementPoint *[ROW_NUMBER]();
    for (int i = 0; i < ROW_NUMBER; ++i) {
        mpsTable[i] = new MeasurementPoint[COLUMN_NUMBER]();
    }
    return mpsTable;
}

void TimeMeasurement::deleteMeasurementPointTable(MeasurementPoint **mpsTable) {
    for (int i = 0; i < ROW_NUMBER; ++i) {
        delete[] mpsTable[i];
    }
    delete[] mpsTable;
}

void TimeMeasurement::divideEachTimeByDrawsNumber(MeasurementPoint **mps) {
    for (int i = 0; i < ROW_NUMBER; ++i) {
        for (int j = 0; j < COLUMN_NUMBER; ++j) {
            mps[i][j].time /= DRAWS_NUMBER;
        }
    }
}

void TimeMeasurement::analyzeMinimalSpanningTreeTime() {
    MeasurementPoint **mpsKruskalList = createMeasurementPointTable();
    MeasurementPoint **mpsKruskalMatrix = createMeasurementPointTable();
    MeasurementPoint **mpsPrimList = createMeasurementPointTable();
    MeasurementPoint **mpsPrimMatrix = createMeasurementPointTable();
    int mstTotalWeight;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "analyzeMinimalSpanningTreeTime: draw No. " + std::to_string(draw) + "...";
        for (int i = 0; i < ROW_NUMBER; ++i) {
            for (int j = 0; j < COLUMN_NUMBER; ++j) {
                GraphUtils::loadRandomGraphWithConstraints(&listGraph, GraphUtils::Algorithm::Kruskal,
                                                           IGraph::GraphStructure::AdjacencyList, nVertexValues[i],
                                                           densityValues[j]);
                matrixGraph = new MatrixGraph(dynamic_cast<ListGraph *>(listGraph));

                mpsKruskalList[i][j].nVertex = nVertexValues[i];
                mpsKruskalList[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findMinimalSpanningTreeKruskal(listGraph, &mstTotalWeight);
                });

                mpsKruskalMatrix[i][j].nVertex = nVertexValues[i];
                mpsKruskalMatrix[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findMinimalSpanningTreeKruskal(matrixGraph, &mstTotalWeight);
                });

                mpsPrimList[i][j].nVertex = nVertexValues[i];
                mpsPrimList[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findMinimalSpanningTreePrim(listGraph, &mstTotalWeight);
                });

                mpsPrimMatrix[i][j].nVertex = nVertexValues[i];
                mpsPrimMatrix[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findMinimalSpanningTreePrim(matrixGraph, &mstTotalWeight);
                });
                delete listGraph;
                delete matrixGraph;
            }
        }
        cout << "saved!" << endl;
    }
    divideEachTimeByDrawsNumber(mpsKruskalList);
    saveTimeDataToFile("minimal_spanning_tree/kruskal_list.csv", mpsKruskalList);
    deleteMeasurementPointTable(mpsKruskalList);

    divideEachTimeByDrawsNumber(mpsKruskalMatrix);
    saveTimeDataToFile("minimal_spanning_tree/kruskal_matrix.csv", mpsKruskalMatrix);
    deleteMeasurementPointTable(mpsKruskalMatrix);

    divideEachTimeByDrawsNumber(mpsPrimList);
    saveTimeDataToFile("minimal_spanning_tree/prim_list.csv", mpsPrimList);
    deleteMeasurementPointTable(mpsPrimList);

    divideEachTimeByDrawsNumber(mpsPrimMatrix);
    saveTimeDataToFile("minimal_spanning_tree/prim_matrix.csv", mpsPrimMatrix);
    deleteMeasurementPointTable(mpsPrimMatrix);
}

void TimeMeasurement::analyzeShortestPathTime() {
    MeasurementPoint **mpsDijkstraList = createMeasurementPointTable();
    MeasurementPoint **mpsDijkstraMatrix = createMeasurementPointTable();
    MeasurementPoint **mpsBellmanFordList = createMeasurementPointTable();
    MeasurementPoint **mpsBellmanFordMatrix = createMeasurementPointTable();
    int startVertexID, endVertexID, shortestPathLength, *predecessorsOnPath;
    bool pathExists;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "analyzeShortestPathTime: draw No. " + std::to_string(draw) + "...";
        for (int i = 0; i < ROW_NUMBER; ++i) {
            for (int j = 0; j < COLUMN_NUMBER; ++j) {
                GraphUtils::loadRandomGraphWithConstraints(&listGraph, GraphUtils::Algorithm::Dijkstra,
                                                           IGraph::GraphStructure::AdjacencyList, nVertexValues[i],
                                                           densityValues[j]);
                matrixGraph = new MatrixGraph(dynamic_cast<ListGraph *>(listGraph));
                predecessorsOnPath = new int[matrixGraph->getVertexCount()];
                startVertexID = GraphUtils::getRand(0, matrixGraph->getVertexCount());
                do {
                    endVertexID = GraphUtils::getRand(0, matrixGraph->getVertexCount());
                } while (startVertexID == endVertexID);

                mpsDijkstraList[i][j].nVertex = nVertexValues[i];
                mpsDijkstraList[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findShortestPathDijkstraHeap(listGraph, startVertexID, endVertexID,
                                                                  predecessorsOnPath, &shortestPathLength);
                });

                mpsDijkstraMatrix[i][j].nVertex = nVertexValues[i];
                mpsDijkstraMatrix[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findShortestPathDijkstraHeap(matrixGraph, startVertexID, endVertexID,
                                                                  predecessorsOnPath, &shortestPathLength);
                });

                mpsBellmanFordList[i][j].nVertex = nVertexValues[i];
                mpsBellmanFordList[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findShortestPathBellmanFord(listGraph, startVertexID, endVertexID, &pathExists,
                                                                 predecessorsOnPath, &shortestPathLength);
                });

                mpsBellmanFordMatrix[i][j].nVertex = nVertexValues[i];
                mpsBellmanFordMatrix[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findShortestPathBellmanFord(matrixGraph, startVertexID, endVertexID, &pathExists,
                                                                 predecessorsOnPath, &shortestPathLength);
                });
                delete[] predecessorsOnPath;
                delete listGraph;
                delete matrixGraph;
            }
        }
        cout << "saved!" << endl;
    }
    divideEachTimeByDrawsNumber(mpsDijkstraList);
    saveTimeDataToFile("shortest_path/dijkstra_list.csv", mpsDijkstraList);
    deleteMeasurementPointTable(mpsDijkstraList);

    divideEachTimeByDrawsNumber(mpsDijkstraMatrix);
    saveTimeDataToFile("shortest_path/dijkstra_matrix.csv", mpsDijkstraMatrix);
    deleteMeasurementPointTable(mpsDijkstraMatrix);

    divideEachTimeByDrawsNumber(mpsBellmanFordList);
    saveTimeDataToFile("shortest_path/bellman_ford_list.csv", mpsBellmanFordList);
    deleteMeasurementPointTable(mpsBellmanFordList);

    divideEachTimeByDrawsNumber(mpsBellmanFordMatrix);
    saveTimeDataToFile("shortest_path/bellman_ford_matrix.csv", mpsBellmanFordMatrix);
    deleteMeasurementPointTable(mpsBellmanFordMatrix);
}

void TimeMeasurement::analyzeMaximalFlowTime() {
    MeasurementPoint **mpsFordFulkersonBfsList = createMeasurementPointTable();
    MeasurementPoint **mpsFordFulkersonBfsMatrix = createMeasurementPointTable();
    MeasurementPoint **mpsFordFulkersonDfsList = createMeasurementPointTable();
    MeasurementPoint **mpsFordFulkersonDfsMatrix = createMeasurementPointTable();
    int maxFlow, endVertexID;
    const int startVertexID = 0;
    for (int draw = 0; draw < DRAWS_NUMBER; ++draw) {
        cout << "analyzeMaximalFlowTime: draw No. " + std::to_string(draw) + "...";
        for (int i = 0; i < ROW_NUMBER; ++i) {
            for (int j = 0; j < COLUMN_NUMBER; ++j) {
                GraphUtils::loadRandomGraphWithConstraints(&listGraph, GraphUtils::Algorithm::Ford_Fulkerson_BFS,
                                                           IGraph::GraphStructure::AdjacencyList, nVertexValues[i],
                                                           densityValues[j]);
                matrixGraph = new MatrixGraph(dynamic_cast<ListGraph *>(listGraph));
                endVertexID = matrixGraph->getVertexCount() - 1;

                mpsFordFulkersonBfsList[i][j].nVertex = nVertexValues[i];
                mpsFordFulkersonBfsList[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findMaximalFlowFordFulkersonBfs(listGraph, startVertexID, endVertexID, &maxFlow);
                });

                mpsFordFulkersonBfsMatrix[i][j].nVertex = nVertexValues[i];
                mpsFordFulkersonBfsMatrix[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findMaximalFlowFordFulkersonBfs(matrixGraph, startVertexID, endVertexID, &maxFlow);
                });

                mpsFordFulkersonDfsList[i][j].nVertex = nVertexValues[i];
                mpsFordFulkersonDfsList[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findMaximalFlowFordFulkersonDfs(listGraph, startVertexID, endVertexID, &maxFlow);
                });

                mpsFordFulkersonDfsMatrix[i][j].nVertex = nVertexValues[i];
                mpsFordFulkersonDfsMatrix[i][j].time += countTime([&]() -> void {
                    GraphAlgorithms::findMaximalFlowFordFulkersonDfs(matrixGraph, startVertexID, endVertexID, &maxFlow);
                });

                delete listGraph;
                delete matrixGraph;
            }
        }
        cout << "saved!" << endl;
    }
    divideEachTimeByDrawsNumber(mpsFordFulkersonBfsList);
    saveTimeDataToFile("maximal_flow/ford_fulkerson_bfs_list.csv", mpsFordFulkersonBfsList);
    deleteMeasurementPointTable(mpsFordFulkersonBfsList);

    divideEachTimeByDrawsNumber(mpsFordFulkersonBfsMatrix);
    saveTimeDataToFile("maximal_flow/ford_fulkerson_bfs_matrix.csv", mpsFordFulkersonBfsMatrix);
    deleteMeasurementPointTable(mpsFordFulkersonBfsMatrix);

    divideEachTimeByDrawsNumber(mpsFordFulkersonDfsList);
    saveTimeDataToFile("maximal_flow/ford_fulkerson_dfs_list.csv", mpsFordFulkersonDfsList);
    deleteMeasurementPointTable(mpsFordFulkersonDfsList);

    divideEachTimeByDrawsNumber(mpsFordFulkersonDfsMatrix);
    saveTimeDataToFile("maximal_flow/ford_fulkerson_dfs_matrix.csv", mpsFordFulkersonDfsMatrix);
    deleteMeasurementPointTable(mpsFordFulkersonDfsMatrix);
}
