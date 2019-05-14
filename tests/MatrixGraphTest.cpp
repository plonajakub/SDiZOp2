#include "MatrixGraphTest.h"

void MatrixGraphTest::run() {
    testToString();
}

void MatrixGraphTest::testToString() {
    cout << "### MatrixGraphTest::testToString() start ###" << endl;
    MatrixGraph mg(MatrixGraph::GraphType::Directed, 4);
    mg.addEdge(0, 1, 5);
    mg.addEdge(0, 2, 10);
    mg.addEdge(1, 2, 15);
    mg.addEdge(3, 2, 20);
    mg.addEdge(2, 3, 25);
    cout << mg.toString() << endl;
    cout << "### MatrixGraphTest::testToString() end ###" << endl;
}


