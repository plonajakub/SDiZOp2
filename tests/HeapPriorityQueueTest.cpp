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
    queue.enqueue(node);
    node.key = 15;
    queue.enqueue(node);
    node.key = 1;
    queue.enqueue(node);
    node.key = 10;
    queue.enqueue(node);

    assert(queue.dequeue() == 1);
    assert(queue.dequeue() == 5);
    assert(queue.dequeue() == 10);
    assert(queue.dequeue() == 15);
    assert(queue.table.getSize() == 0);
}
