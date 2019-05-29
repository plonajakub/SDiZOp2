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
        cout << endl;
        delete matrixGraph;
        GraphUtils::loadGraphFromTxt(&matrixGraph, IGraph::GraphStructure::IncidenceMatrix,
                                     IGraph::GraphType::Undirected, "undirected_graph.txt");
        delete listGraph;
        GraphUtils::loadGraphFromTxt(&listGraph, IGraph::GraphStructure::AdjacencyList, IGraph::GraphType::Undirected,
                                     "undirected_graph.txt");
        cout << "Graph loaded from the file!" << endl;
    } else if (operationCode == "12") {
        cout << "Enter number of vertices:";
        cin >> nVertex;
        cout << "Enter density [%]:";
        cin >> density;
        cout << endl;
        delete matrixGraph;
        GraphUtils::loadRandomGraphWithConstraints(&matrixGraph, GraphUtils::Algorithm::Kruskal,
                                                   IGraph::GraphStructure::IncidenceMatrix, nVertex, density);
        delete listGraph;
        GraphUtils::loadRandomGraphWithConstraints(&listGraph, GraphUtils::Algorithm::Kruskal,
                                                   IGraph::GraphStructure::AdjacencyList, nVertex, density);
        cout << "Random graph generated!" << endl;
    } else if (operationCode == "13") {
        if (listGraph != nullptr && matrixGraph != nullptr) {
            cout << "--- Incidence matrix graph representation ---" << endl;
            cout << *matrixGraph << endl << endl;
            cout << "--- Adjacency list graph representation ---" << endl;
            cout << *listGraph << endl;
        } else {
            cout << "No graph has been loaded: build a graph first!" << endl;
        }
    } else if (operationCode == "14") {
        IGraph *minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreeKruskal(matrixGraph);
        cout << "Minimal spanning tree (Kruskal - incidence matrix)\n" << *minimalSpanningTree << endl;
        delete minimalSpanningTree;

        minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreeKruskal(listGraph);
        cout << "Minimal spanning tree (Kruskal - adjacency list)\n" << *minimalSpanningTree << endl;
        delete minimalSpanningTree;
    } else if (operationCode == "15") {
        IGraph *minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreePrim(matrixGraph);
        cout << "Minimal spanning tree (Prim - incidence matrix)\n" << *minimalSpanningTree << endl;
        delete minimalSpanningTree;

        minimalSpanningTree = GraphAlgorithms::findMinimalSpanningTreePrim(listGraph);
        cout << "Minimal spanning tree (Prim - adjacency list)\n" << *minimalSpanningTree << endl;
        delete minimalSpanningTree;
        /////////////////////////////////////////////////////////////////
        //// List - operations
        /////////////////////////////////////////////////////////////////
    } else if (operationCode == "21") {
//        cout << endl;
//        try {
//            Table inputData = this->loadDataFromFile("build_list.txt");
//            for (int i = 0; i < inputData.getSize(); ++i) {
//                dll->insertAtEnd(inputData[i]);
//            }
//            cout << "Data successfully loaded into the list!" << endl;
//            cout << "List after load: " << *dll << endl;
//        } catch (const std::ios_base::failure &e) {
//            cout << "List not affected" << endl;
//        }
//    } else if (operationCode == "22") {
//        int value;
//        cout << "Enter a value to be removed:";
//        cin >> value;
//        cout << endl;
//        try {
//            dll->removeByValue(value);
//        } catch (const std::out_of_range &e) {
//            cout << "No such value in the list!" << endl;
//        }
//        cout << "List after removal: " << *dll << endl;
//    } else if (operationCode == "23") {
//        int searchValue, insertValue;
//        cout << "Enter a base value:";
//        cin >> searchValue;
//        cout << "Enter a new value:";
//        cin >> insertValue;
//        cout << endl;
//        dll->insertAfterValue(searchValue, insertValue);
//        cout << "List after insertion: " << *dll << endl;
//    } else if (operationCode == "24") {
//        int value;
//        cout << "Enter value to be searched for in the list:";
//        cin >> value;
//        cout << endl;
//        int index = dll->search(value);
//        if (index != DoublyLinkedList::VALUE_NOT_FOUND) {
//            cout << "Entered value is in the list" << endl;
//        } else {
//            cout << "Entered value is not in the list" << endl;
//        }
//    } else if (operationCode == "25") {
//        cout << endl;
//        cout << "List: " << *dll << endl;
//        /////////////////////////////////////////////////////////////////
//        //// Heap - operations
//        /////////////////////////////////////////////////////////////////
//    } else if (operationCode == "31") {
//        cout << endl;
//        try {
//            Table inputData = this->loadDataFromFile("build_heap.txt");
//            for (int i = 0; i < inputData.getSize(); ++i) {
//                heap->insert(inputData[i]);
//            }
//            cout << "Data successfully loaded into the heap!" << endl;
//            cout << "Heap after load: " << endl << *heap << endl;
//        } catch (const std::ios_base::failure &e) {
//            cout << "Heap not affected" << endl;
//        }
//    } else if (operationCode == "32") {
//        int key;
//        cout << "Enter a key to be removed:";
//        cin >> key;
//        cout << endl;
//        try {
//            heap->remove(key);
//        } catch (const std::invalid_argument &e) {
//            cout << "No such key in the heap!" << endl;
//        }
//        cout << "Heap after removal: " << endl << *heap << endl;
//    } else if (operationCode == "33") {
//        int key;
//        cout << "Enter a new key:";
//        cin >> key;
//        cout << endl;
//        heap->insert(key);
//        cout << "Heap after insertion: " << endl << *heap << endl;
//    } else if (operationCode == "34") {
//        int key;
//        cout << "Enter a key to be searched for in the heap:";
//        cin >> key;
//        cout << endl;
//        int index = heap->search(key);
//        if (index != Heap::KEY_NOT_FOUND) {
//            cout << "Entered key is in the heap" << endl;
//        } else {
//            cout << "Entered key is not in the heap" << endl;
//        }
//    } else if (operationCode == "35") {
//        cout << endl;
//        cout << "Heap: " << endl << *heap << endl;
//        /////////////////////////////////////////////////////////////////
//        //// Red-Black Tree - operations
//        /////////////////////////////////////////////////////////////////
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
    menuOption.description = "Maximal Flow";
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
    menuItem = MenuItem(MenuItem::OperationType::SUBMENU, "Maximal Flow");

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
