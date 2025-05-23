#include <iostream>
#include <memory>
class Node
{
    Node* next;
    Node* prev;
    Node* parent;
    Node* child;
    int value;
public:
    Node(int val) : value(val), next(nullptr), prev(nullptr), parent(nullptr), child(nullptr) {}

    Node* getNext() { return next; }
    Node* getPrev() { return prev; }
    Node* getParent() { return parent; }
    Node* getChild() { return child; }

    int getValue() { return value; }
};

class FibonacciHeap
{
    Node* heap; // points to the min value
    Node* newNode(int value) { std::shared_ptr<Node> node = std::make_shared<Node>(Node(value)); }// create new node
public:
    FibonacciHeap() : heap(nullptr) {} // create the heap

    int getMin() { return heap->getValue(); } // O(1) 
    int insert() {} // O(1)
};


int main() {
    std::cout << "Fibonacci Heap Implementation" << std::endl;
    return 0;
}