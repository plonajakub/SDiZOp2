#include "ConsoleMenu.h"


ConsoleMenu::ConsoleMenu() : nextFreeMenuOperation(0) {
    prepareMenuOperations();
    matrixGraph = nullptr;
    listGraph = nullptr;
}

ConsoleMenu::~ConsoleMenu() {
    delete matrixGraph;
    delete listGraph;
}

void ConsoleMenu::addMenuOperation(const ConsoleMenu::MenuOperation &menuOperation) {
    if (nextFreeMenuOperation == MAX_OPERATIONS_QUANTITY) {
        throw std::out_of_range("ConsoleMenu operation's limit reached");
    }
    menuOperations[nextFreeMenuOperation] = menuOperation;
    ++nextFreeMenuOperation;
}

void ConsoleMenu::start(const std::string &menuCode) {
    int menuControlVariable;
    ProgramState ps = ProgramState::RUNNING;
    while (ps == ProgramState::RUNNING) {
        cout << std::string(70, '#') << endl << endl;
        cout << this->getMenuOperation(menuCode).menuItem.operationName << ":" << endl;
        printMenuOptions(menuCode);
        menuControlVariable = getMenuControlVariable(menuCode);
        ps = chooseMenuOperation(menuCode, menuControlVariable);
    }
}

void ConsoleMenu::printMenuOptions(const std::string &menuCode) {
    MenuItem &menuItem = this->getMenuOperation(menuCode).menuItem;
    MenuItem::allMenuOptions menuOptions = menuItem.getMenuOptions();
    for (int i = 0; i < menuItem.getMenuOptionsSize(); ++i) {
        cout << menuOptions[i].ID << ". " << menuOptions[i].description << endl;
    }
    if (menuCode.empty()) {
        cout << "0. Exit" << endl;
    }
    if (!menuCode.empty()) {
        cout << "0. Return" << endl;
    }
}

ConsoleMenu::MenuOperation &ConsoleMenu::getMenuOperation(const std::string &operationID) {
    for (auto &operation : menuOperations) {
        if (operation.ID == operationID) {
            return operation;
        }
    }
    throw std::invalid_argument("No such MenuOperation");
}

int ConsoleMenu::getMenuControlVariable(const std::string &menuCode) {
    MenuOperation menuOperation = this->getMenuOperation(menuCode);
    int menuControlVariable = -1;
    Operation status = Operation::FAILURE;
    cout << endl << "Choose operation:";
    while (status == Operation::FAILURE) {
        try {
            cin >> menuControlVariable;
            if (menuControlVariable < 0 || menuControlVariable > menuOperation.menuItem.getMenuOptionsSize()) {
                cout << "Wrong operation's ID. Try again: ";
                continue;
            }
            status = Operation::SUCCESS;
        } catch (const std::ios_base::failure &e) {
            cout << "Wrong input. Try again: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max());
            continue;
        }
    }
    return menuControlVariable;
}

ConsoleMenu::ProgramState ConsoleMenu::chooseMenuOperation(const std::string &menuCode, int menuControlVariable) {
    if (menuControlVariable == 0 && !menuCode.empty()) {
        delete matrixGraph;
        matrixGraph = nullptr;
        delete listGraph;
        listGraph = nullptr;
        cout << "--- RETURN ---" << endl;
        return ProgramState::RETURN;
    }
    if (menuControlVariable == 0 && menuCode.empty()) {
        cout << "--- EXIT ---" << endl;
        return ProgramState::EXIT;
    }
    std::string operationCode = menuCode + std::to_string(menuControlVariable);

    if (this->getMenuOperation(operationCode).menuItem.operationType == MenuItem::OperationType::SUBMENU) {
        this->start(operationCode);
        /////////////////////////////////////////////////////////////////
        //// Minimal spanning tree - operations
        /////////////////////////////////////////////////////////////////
    } else if (operationCode == "11") {
        delete matrixGraph;
        GraphUtils::loadGraphFromTxt(&matrixGraph, IGraph::GraphStructure::IncidenceMatrix,
                                     IGraph::GraphType::Undirected, "undirected_graph.txt");
        delete listGraph;
        listGraph = new ListGraph(dynamic_cast<MatrixGraph *>(matrixGraph));
        cout << "Graphs has been loaded from the file!" << endl;
    } else if (operationCode == "12") {
        cout << "Enter number of vertices:";
        cin >> nVertex;
        cout << "Enter density [%]:";
        cin >> density;
        cout << endl;
        delete matrixGraph;
        try {
            GraphUtils::loadRandomGraphWithConstraints(&matrixGraph, GraphUtils::Algorithm::Kruskal,
                                                       IGraph::GraphStructure::IncidenceMatrix, nVertex, density);
        } catch (const std::invalid_argument &e) {
            cout << e.what() << endl;
            cout << "Try again..." << endl;
            return ProgramState::RUNNING;
        }
        delete listGraph;
        listGraph = new ListGraph(dynamic_cast<MatrixGraph *>(matrixGraph));
        cout << "Random graphs generated!" << endl;
    } else if (operationCode == "13") {
        if (listGraph != nullptr && matrixGraph != nullptr) {
            cout << "--------- Incidence matrix graph representation ---------" << endl;
            cout << *matrixGraph << endl << endl;
            cout << "--------- Adjacency lists graph representation ---------" << endl;
            cout << *listGraph << endl;
        } else {
            cout << "Error: graphs have not been loaded!" << endl;
        }
    } else if (operationCode == "14") {
        if (listGraph != nullptr && matrixGraph != nullptr) {
            int mstTotalWeight;
            IGraph *minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreeKruskal(matrixGraph, &mstTotalWeight);
            cout << "Minimal spanning tree (Kruskal - incidence matrix)\n" << *minimalSpanningTree << endl;
            cout << "Total weight = " << mstTotalWeight << endl << endl;
            delete minimalSpanningTree;

            minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreeKruskal(listGraph, &mstTotalWeight);
            cout << "Minimal spanning tree (Kruskal - adjacency lists)\n" << *minimalSpanningTree << endl;
            cout << "Total weight = " << mstTotalWeight << endl;
            delete minimalSpanningTree;
        } else {
            cout << "Error: graphs have not been loaded!" << endl;
        }
    } else if (operationCode == "15") {
        if (listGraph != nullptr && matrixGraph != nullptr) {
            int mstTotalWeight;
            IGraph *minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreePrim(matrixGraph, &mstTotalWeight);
            cout << "Minimal spanning tree (Prim - incidence matrix)\n" << *minimalSpanningTree << endl;
            cout << "Total weight = " << mstTotalWeight << endl << endl;
            delete minimalSpanningTree;

            minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreePrim(listGraph, &mstTotalWeight);
            cout << "Minimal spanning tree (Prim - adjacency lists)\n" << *minimalSpanningTree << endl;
            cout << "Total weight = " << mstTotalWeight << endl;
            delete minimalSpanningTree;
        } else {
            cout << "Error: graphs have not been loaded!" << endl;
        }
        /////////////////////////////////////////////////////////////////
        //// Shortest path - operations
        /////////////////////////////////////////////////////////////////
    } else if (operationCode == "21") {
        delete matrixGraph;
        GraphUtils::loadGraphFromTxt(&matrixGraph, IGraph::GraphStructure::IncidenceMatrix,
                                     IGraph::GraphType::Directed, "directed_graph.txt");
        delete listGraph;
        listGraph = new ListGraph(dynamic_cast<MatrixGraph *>(matrixGraph));
        cout << "Graphs has been loaded from the file!" << endl;
    } else if (operationCode == "22") {
        cout << "Enter number of vertices:";
        cin >> nVertex;
        cout << "Enter density [%]:";
        cin >> density;
        cout << endl;
        delete matrixGraph;
        try {
            GraphUtils::loadRandomGraphWithConstraints(&matrixGraph, GraphUtils::Algorithm::Dijkstra,
                                                       IGraph::GraphStructure::IncidenceMatrix, nVertex, density);
        } catch (const std::invalid_argument &e) {
            cout << e.what() << endl;
            cout << "Try again..." << endl;
            return ProgramState::RUNNING;
        }
        delete listGraph;
        listGraph = new ListGraph(dynamic_cast<MatrixGraph *>(matrixGraph));
        cout << "Random graphs generated!" << endl;
    } else if (operationCode == "23") {
        if (listGraph != nullptr && matrixGraph != nullptr) {
            cout << "--------- Incidence matrix graph representation ---------" << endl;
            cout << *matrixGraph << endl << endl;
            cout << "--------- Adjacency lists graph representation ---------" << endl;
            cout << *listGraph << endl;
        } else {
            cout << "Error: graphs have not been loaded!" << endl;
        }
    } else if (operationCode == "24") {
        if (listGraph != nullptr && matrixGraph != nullptr) {
            int *predecessorsOnPath = new int[listGraph->getVertexCount()];
            DoublyLinkedList<int> shortestPath;
            int shortestPathLength;
            int startVertexID;
            int endVertexID;
            cout << "Enter start vertex ID:";
            cin >> startVertexID;
            if (startVertexID < 0 || startVertexID >= listGraph->getVertexCount()) {
                cout << "Error: invalid start vertex ID" << endl;
                cout << "Try again..." << endl;
                return ProgramState::RUNNING;
            }
            cout << "Enter end vertex ID:";
            cin >> endVertexID;
            if (endVertexID < 0 || endVertexID >= listGraph->getVertexCount()) {
                cout << "Error: invalid end vertex ID" << endl;
                cout << "Try again..." << endl;
                return ProgramState::RUNNING;
            }
            cout << endl;

            GraphAlgorithms::findShortestPathDijkstraHeap(matrixGraph, startVertexID, endVertexID, predecessorsOnPath,
                                                          &shortestPathLength);
            shortestPath = GraphAlgorithms::decodeShortestPath(predecessorsOnPath, startVertexID, endVertexID);
            if (shortestPath.getIterator().getData() != -1) {
                cout << "Shortest path from " << startVertexID << " to " << endVertexID
                     << " (Dijkstra - incidence matrix) is: "
                     << shortestPath << endl;
                cout << "Total weight = " << shortestPathLength << endl;
            } else {
                cout << "Shortest path from " << startVertexID << " to " << endVertexID
                     << " (Dijkstra - incidence matrix) does not exist!" << endl;
            }
            GraphAlgorithms::findShortestPathDijkstraHeap(listGraph, startVertexID, endVertexID, predecessorsOnPath,
                                                          &shortestPathLength);
            shortestPath = GraphAlgorithms::decodeShortestPath(predecessorsOnPath, startVertexID, endVertexID);
            if (shortestPath.getIterator().getData() != -1) {
                cout << "Shortest path from " << startVertexID << " to " << endVertexID
                     << " (Dijkstra - adjacency lists) is: "
                     << shortestPath << endl;
                cout << "Total weight = " << shortestPathLength << endl;
            } else {
                cout << "Shortest path from " << startVertexID << " to " << endVertexID
                     << " (Dijkstra - adjacency lists) does not exist!" << endl;
            }

            delete[] predecessorsOnPath;
        } else {
            cout << "Error: graphs have not been loaded!" << endl;
        }
    } else if (operationCode == "25") {
        if (listGraph != nullptr && matrixGraph != nullptr) {
            int *predecessorsOnPath = new int[listGraph->getVertexCount()];
            bool pathExists;
            DoublyLinkedList<int> shortestPath;
            int shortestPathLength;
            int startVertexID;
            int endVertexID;
            cout << "Enter start vertex ID:";
            cin >> startVertexID;
            if (startVertexID < 0 || startVertexID >= listGraph->getVertexCount()) {
                cout << "Error: invalid start vertex ID" << endl;
                cout << "Try again..." << endl;
                return ProgramState::RUNNING;
            }
            cout << "Enter end vertex ID:";
            cin >> endVertexID;
            if (endVertexID < 0 || endVertexID >= listGraph->getVertexCount()) {
                cout << "Error: invalid end vertex ID" << endl;
                cout << "Try again..." << endl;
                return ProgramState::RUNNING;
            }
            cout << endl;

            GraphAlgorithms::findShortestPathBellmanFord(matrixGraph, startVertexID, endVertexID, &pathExists,
                                                         predecessorsOnPath,
                                                         &shortestPathLength);
            shortestPath = GraphAlgorithms::decodeShortestPath(predecessorsOnPath, startVertexID, endVertexID);
            if (shortestPath.getIterator().getData() != -1) {
                cout << "Shortest path from " << startVertexID << " to " << endVertexID
                     << " (Bellman-Ford - incidence matrix) is: "
                     << shortestPath << endl;
                cout << "Total weight = " << shortestPathLength << endl;
            } else if (!pathExists) {
                cout << "Error: graph contains negative cycle" << endl;
            } else {
                cout << "Shortest path from " << startVertexID << " to " << endVertexID
                     << " (Bellman-Ford - incidence matrix) does not exist!" << endl;
            }

            GraphAlgorithms::findShortestPathBellmanFord(listGraph, startVertexID, endVertexID, &pathExists,
                                                         predecessorsOnPath,
                                                         &shortestPathLength);
            shortestPath = GraphAlgorithms::decodeShortestPath(predecessorsOnPath, startVertexID, endVertexID);
            if (shortestPath.getIterator().getData() != -1) {
                cout << "Shortest path from " << startVertexID << " to " << endVertexID
                     << " (Bellman-Ford - adjacency lists) is: "
                     << shortestPath << endl;
                cout << "Total weight = " << shortestPathLength << endl;
            } else if (!pathExists) {
                cout << "Error: graph contains negative cycle" << endl;
            } else {
                cout << "Shortest path from " << startVertexID << " to " << endVertexID
                     << " (Bellman-Ford - adjacency lists) does not exist!" << endl;
            }
            delete[] predecessorsOnPath;
        } else {
            cout << "Error: graphs have not been loaded!" << endl;
        }
        /////////////////////////////////////////////////////////////////
        //// Maximal flow - operations
        /////////////////////////////////////////////////////////////////
    } else if (operationCode == "31") {
        delete matrixGraph;
        GraphUtils::loadGraphFromTxt(&matrixGraph, IGraph::GraphStructure::IncidenceMatrix,
                                     IGraph::GraphType::Directed, "capacity_network.txt");
        delete listGraph;
        listGraph = new ListGraph(dynamic_cast<MatrixGraph *>(matrixGraph));
        cout << "Graphs has been loaded from the file!" << endl;
    } else if (operationCode == "32") {
        cout << "Enter number of vertices:";
        cin >> nVertex;
        cout << "Enter density [%]:";
        cin >> density;
        cout << endl;
        delete matrixGraph;
        try {
            GraphUtils::loadRandomGraphWithConstraints(&matrixGraph, GraphUtils::Algorithm::Ford_Fulkerson_BFS,
                                                       IGraph::GraphStructure::IncidenceMatrix, nVertex, density);
        } catch (const std::invalid_argument &e) {
            cout << e.what() << endl;
            cout << "Try again..." << endl;
            return ProgramState::RUNNING;
        }
        delete listGraph;
        listGraph = new ListGraph(dynamic_cast<MatrixGraph *>(matrixGraph));
        cout << "Random graphs generated!" << endl;
    } else if (operationCode == "33") {
        if (listGraph != nullptr && matrixGraph != nullptr) {
            cout << "--------- Incidence matrix graph representation ---------" << endl;
            cout << *matrixGraph << endl << endl;
            cout << "--------- Adjacency lists graph representation ---------" << endl;
            cout << *listGraph << endl;
        } else {
            cout << "Error: graphs have not been loaded!" << endl;
        }
    } else if (operationCode == "34") {
        if (listGraph != nullptr && matrixGraph != nullptr) {
            IGraph *flowNetwork;
            int maxFlow;
            int startVertexID;
            int endVertexID;
            cout << "Enter start vertex ID:";
            cin >> startVertexID;
            if (startVertexID < 0 || startVertexID >= listGraph->getVertexCount()) {
                cout << "Error: invalid start vertex ID" << endl;
                cout << "Try again..." << endl;
                return ProgramState::RUNNING;
            }
            cout << "Enter end vertex ID:";
            cin >> endVertexID;
            if (endVertexID < 0 || endVertexID >= listGraph->getVertexCount()) {
                cout << "Error: invalid end vertex ID" << endl;
                cout << "Try again..." << endl;
                return ProgramState::RUNNING;
            }
            cout << endl;

            flowNetwork = GraphAlgorithms::findMaximalFlowFordFulkersonBfs(matrixGraph, startVertexID, endVertexID,
                                                                           &maxFlow);
            cout << "Flow network (Ford-Fulkerson (BFS) - incidence matrix)\n" << *flowNetwork << endl;
            cout << "Max flow = " << maxFlow << endl;
            delete flowNetwork;

            flowNetwork = GraphAlgorithms::findMaximalFlowFordFulkersonBfs(listGraph, startVertexID, endVertexID,
                                                                           &maxFlow);
            cout << "Flow network (Ford-Fulkerson (BFS) - adjacency lists)\n" << *flowNetwork << endl;
            cout << "Max flow = " << maxFlow << endl;
            delete flowNetwork;
        } else {
            cout << "Error: graphs have not been loaded!" << endl;
        }
    } else if (operationCode == "35") {
        if (listGraph != nullptr && matrixGraph != nullptr) {
            IGraph *flowNetwork;
            int maxFlow;
            int startVertexID;
            int endVertexID;
            cout << "Enter start vertex ID:";
            cin >> startVertexID;
            if (startVertexID < 0 || startVertexID >= listGraph->getVertexCount()) {
                cout << "Error: invalid start vertex ID" << endl;
                cout << "Try again..." << endl;
                return ProgramState::RUNNING;
            }
            cout << "Enter end vertex ID:";
            cin >> endVertexID;
            if (endVertexID < 0 || endVertexID >= listGraph->getVertexCount()) {
                cout << "Error: invalid end vertex ID" << endl;
                cout << "Try again..." << endl;
                return ProgramState::RUNNING;
            }
            cout << endl;

            flowNetwork = GraphAlgorithms::findMaximalFlowFordFulkersonDfs(matrixGraph, startVertexID, endVertexID,
                                                                           &maxFlow);
            cout << "Flow network (Ford-Fulkerson (DFS) - incidence matrix)\n" << *flowNetwork << endl;
            cout << "Max flow = " << maxFlow << endl;
            delete flowNetwork;


            flowNetwork = GraphAlgorithms::findMaximalFlowFordFulkersonDfs(listGraph, startVertexID, endVertexID,
                                                                           &maxFlow);
            cout << "Flow network (Ford-Fulkerson (DFS) - adjacency lists)\n" << *flowNetwork << endl;
            cout << "Max flow = " << maxFlow << endl;
            delete flowNetwork;
        } else {
            cout << "Error: graphs have not been loaded!" << endl;
        }
    }
    return ProgramState::RUNNING;
}

void ConsoleMenu::prepareMenuOperations() {
    MenuOperation menuOperation;
    MenuItem menuItem;
    MenuItem::MenuOption menuOption;

    ////////////////////////////////////////////////////////////////////
    // Main menu
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "";
    menuItem = MenuItem(MenuItem::OperationType::SUBMENU, "Main menu");

    menuOption.ID = "1";
    menuOption.description = "Minimal spanning tree";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "2";
    menuOption.description = "Shortest path";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "3";
    menuOption.description = "Maximal flow";
    menuItem.addMenuOption(menuOption);

    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    ////////////////////////////////////////////////////////////////////
    // Minimal spanning tree
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "1";
    menuItem = MenuItem(MenuItem::OperationType::SUBMENU, "Minimal spanning tree");

    menuOption.ID = "1";
    menuOption.description = "Load a graph from file";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "2";
    menuOption.description = "Generate random graph";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "3";
    menuOption.description = "Show graph";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "4";
    menuOption.description = "Solve with Kruskal's algorithm";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "5";
    menuOption.description = "Solve with Prim's algorithm";
    menuItem.addMenuOption(menuOption);

    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);


    ////////////////////////////////////////////////////////////////////
    // Minimal spanning tree - operations
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "11";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Load a graph from file");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "12";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Generate random graph");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "13";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Show graph");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "14";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Solve with Kruskal's algorithm");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "15";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Solve with Prim's algorithm");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    ////////////////////////////////////////////////////////////////////
    // Shortest path
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "2";
    menuItem = MenuItem(MenuItem::OperationType::SUBMENU, "Shortest path");

    menuOption.ID = "1";
    menuOption.description = "Load a graph from file";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "2";
    menuOption.description = "Generate random graph";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "3";
    menuOption.description = "Show graph";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "4";
    menuOption.description = "Solve with Dijkstra's algorithm";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "5";
    menuOption.description = "Solve with Bellman-Ford's algorithm";
    menuItem.addMenuOption(menuOption);

    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);


    ////////////////////////////////////////////////////////////////////
    // Shortest path - operations
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "21";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Load a graph from file");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "22";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Generate random graph");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "23";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Show graph");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "24";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Solve with Dijkstra's algorithm");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "25";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Solve with Bellman-Ford's algorithm");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    ////////////////////////////////////////////////////////////////////
    // Maximal Flow
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "3";
    menuItem = MenuItem(MenuItem::OperationType::SUBMENU, "Maximal flow");

    menuOption.ID = "1";
    menuOption.description = "Load a graph from file";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "2";
    menuOption.description = "Generate random graph";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "3";
    menuOption.description = "Show graph";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "4";
    menuOption.description = "Solve with Ford-Fulkerson's algorithm (BFS)";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "5";
    menuOption.description = "Solve with Ford-Fulkerson's algorithm (DFS)";
    menuItem.addMenuOption(menuOption);

    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);


    ////////////////////////////////////////////////////////////////////
    // Maximal Flow - operations
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "31";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Load a graph from file");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "32";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Generate random grapht");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "33";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Show graph");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "34";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Solve with Ford-Fulkerson's algorithm (BFS)");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "35";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Solve with Ford-Fulkerson's algorithm (DFS)");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

}
