#include "HeapPriorityQueueTest.h"

#define pStartInfo(method) cout << "##### HeapPriorityQueueTest::" << (method) << "() start #####" << endl
#define pEndInfo(method) cout << "%%%%% HeapPriorityQueueTest::" << (method) << "() end %%%%%" << endl << endl

void HeapPriorityQueueTest::run() {
    pStartInfo("testEnqueue");
    testEnqueue();
    pEndInfo("testEnqueue");

    pStartInfo("testExtractFront");
    testExtractFront();
    pEndInfo("testExtractFront");
}

void HeapPriorityQueueTest::testEnqueue() {
    HeapPriorityQueue<int> queue(HeapPriorityQueue<int>::Type::Min);
    QueueNode<int> node;
    node.key = 5;
    queue.enqueue(node);
    node.key = 15;
    queue.enqueue(node);
    node.key = 1;
    queue.enqueue(node);
    node.key = 10;
    queue.enqueue(node);
    assert(queue.table.getSize() == 4);
    assert(queue.table[0].key == 1);
    assert(queue.table[1].key == 10);
    assert(queue.table[2].key == 5);
    assert(queue.table[3].key == 15);
}

void HeapPriorityQueueTest::testExtractFront() {
    HeapPriorityQueue<int> queue(HeapPriorityQueue<int>::Type::Min);
    QueueNode<int> node;
    node.key = 5;
    node.data = 11;
    queue.enqueue(node);
    node.key = 15;
    node.data = 13;
    queue.enqueue(node);
    node.key = 1;
    node.data = 10;
    queue.enqueue(node);
    node.key = 10;
    node.data = 12;
    queue.enqueue(node);

    assert(queue.dequeue() == 10);
    assert(queue.dequeue() == 11);
    assert(queue.dequeue() == 12);
    assert(queue.dequeue() == 13);
    assert(queue.table.getSize() == 0);
}
