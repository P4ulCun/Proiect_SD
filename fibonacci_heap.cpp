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
    friend class FibonacciHeap;
    Node(int val) : value(val), next(nullptr), 
    prev(nullptr), parent(nullptr), child(nullptr),
    degree(0), marked(false) {}

    Node* getNext() { return next; }
    Node* getPrev() { return prev; }
    Node* getParent() { return parent; }
    Node* getChild() { return child; }
    int degree;
    bool marked;

    int getKey() { return value; }
    
};

class FibonacciHeap
{
    Node* heap; // points to the min value
public:
    FibonacciHeap() : heap(nullptr) {} // create the heap
    ~FibonacciHeap()
    {
        if (heap)
            PdeleteHeap(heap);
    }

    int getMin() { return heap->getKey(); } // O(1) 

    Node* insert(int value)
    {
        Node* node = PnewNode(value);
        heap = Pmerge(heap, node);
        return node;
    } // O(1)

    int removeMin() // O(log n)
    {
        Node* old = heap;

        // remove the min node from the heap
        Punmark_unParent(heap -> child);
        if (heap -> next == heap)
            heap = heap -> child; // if no siblings, set the child as the new heap
        else
        {
            heap -> next -> prev = heap -> prev;
            heap -> prev -> next = heap -> next;
            // cut out the old min and append its children to the heap (top)
            heap = Pmerge(heap -> next, heap -> child);
        }
        if (heap == nullptr)
            return old -> value; // if heap is empty, return the value of the removed node

        // merge trees by their degree
        Node* degrees[100] = {nullptr};

        while (true)
        {
            if (degrees[heap -> degree] == nullptr)
                degrees[heap -> degree] = heap;
            else
            {
                Node* d = degrees[heap -> degree];
                if (d == heap)
                    break;
                
                 // make the bigger tree root a child of the smaller tree root
                if (heap -> value < d -> value)
                {
                    // d is bigger
                    d -> prev -> next = d -> next;
                    d -> next -> prev = d -> prev;
                    PaddChild(heap, d);
                }
                else
                {
                    // heap is bigger 
                    d -> prev -> next = d -> next;
                    d -> next -> prev = d -> prev;
                    if (heap -> next = heap)
                    {
                        // if heap has no siblings
                        d -> next = d -> prev = d; // make it a single node
                        PaddChild(d, heap);
                        heap = d; // set the new min
                    }
                    else
                    {
                        heap -> prev -> next = d;
                        heap -> next -> prev = d;
                        d -> next = heap -> next;
                        d -> prev = heap -> prev;
                        // if heap has siblings, interchange the heap and d nodes, 
                        // then add heap as a child of d
                        PaddChild(d, heap);
                        heap = d;
                    }
                }
                continue; // continue to the next degree
            }

            heap = heap -> next; // move to the next tree in the heap
        }

        // find the new min node in the circular linked list of head nodes
        Node* min = heap;
        Node* start = heap;
        do
        {
            if (heap -> value < min -> value)
                min = heap;
            heap = heap -> next;
        } while (heap != start);

        heap = min; // set the new min node as the heap

        delete old;
        return old -> value;
    }

    void decreaseKey(Node* node, int value) // amortized time is O(1)
    {
        if (node -> value < value) // change nothing
            return;
        
        // need to update node and cut out mini heap
        node -> value = value;
        if (node -> parent)
        {
            if (node -> value < node -> parent -> value)
            // if new node value is not in a good spot [check fib heap proprieties]
            // i.e. parent must be smaller than child
            {
                heap = Pcut(heap, node);
                Node* parent = node -> parent;
                node -> parent = nullptr;
                // cut recursively if parent is marked
                while (parent != nullptr && parent -> marked)
                {
                    heap = Pcut(heap, parent);
                    node = parent;
                    parent = node -> parent;
                    node -> parent = nullptr;
                }

                if (parent != nullptr && parent -> parent != nullptr) // dont mark head node
                    parent -> marked = true; // mark the parent
            }
            else
            {
                // if node is a head, check if it is the min and update
                if (node -> value < heap -> value)
                    heap = node;
            }
        }
    }


private:
    Node* PnewNode(int value)
    {
        Node* node = new Node(value);
        node -> next = node ->prev = node;
        return node;
    }

    Node* Pmerge(Node* a, Node* b) {
        // if either heap is empty return the non empty one
        if (a == nullptr) return b;
        if (b == nullptr) return a;

        if(a->value>b->value) {
			Node* temp=a;
			a=b;
			b=temp;
		}
        // a holds the lower value

        // merge two heaps
        Node* aNext = a -> next;
		Node* bPrev = b -> prev;
		a -> next = b;
		b -> prev = a;
        aNext -> prev = bPrev;
        bPrev -> next = aNext;
        return a;
    }

    Node* Pcut(Node* heap, Node* node)
    {
        if (node -> next == node) // if only child; node has no siblings
            node -> parent -> child = nullptr;
        else
        {
            // if child has siblings, cut the node and update pointers
            node -> next -> prev = node -> prev;
            node -> prev -> next = node -> next;
            node -> parent -> child = node -> next;
        }

        node -> next = node -> prev = node; // make it a single node; a single heap
        node -> marked = false;

        return Pmerge(heap, node); // merge the node with the heap
    }

    void Punmark_unParent(Node* node)
    {
        if (node == nullptr)
            return; 
        
        Node* curr = node;
        do {
            curr -> marked = false;
            curr -> parent = nullptr;
            curr = curr -> next;
        } while (curr != node);
    }

    void PaddChild(Node* parent, Node* child)
    {
        child -> prev = child -> next = child; // make it a single node
        child -> parent = parent;
        parent -> degree++;
        parent -> child = Pmerge(parent -> child, child);
    }

    void PdeleteHeap(Node* node)
    {
        if (node == nullptr)
            return;

        Node* curr = node;
        do {
            Node* nextNode = curr;
            curr = curr -> next;
            PdeleteHeap(nextNode -> child);
        } while (curr != node);
    }
};


int main() {
    std::cout << "Fibonacci-Heap Implementation:\n" << std::endl;

    FibonacciHeap fibHeap;
    fibHeap.insert(1);
    fibHeap.insert(2);
    fibHeap.insert(3);
    fibHeap.insert(4);
    fibHeap.insert(5);
    std::cout << "Minimum value: " << fibHeap.getMin() << std::endl;
    
    int min = fibHeap.removeMin();
    std::cout << "Removed minimum value: " << min << std::endl;

    std::cout << "New minimum value: " << fibHeap.getMin() << std::endl;

    Node *n1 = fibHeap.insert(6);
    Node *n2 = fibHeap.insert(7);
    fibHeap.decreaseKey(n1, 0);
    std:: cout << "Old min value: " << fibHeap.removeMin() << std::endl;
    std:: cout << "New min value after decreasing key: " << fibHeap.getMin() << std::endl;
    return 0;
}