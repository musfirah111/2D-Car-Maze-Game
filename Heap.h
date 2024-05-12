//Muneeb ur Rehman  22i2702
//Musfirah Zunnoon  22i2692


#include <iostream>
#include <algorithm> // header for swap and copy
using namespace std;

template <typename T1, typename T2>
class Heap   //heap for as a minimum priority queue
{
private:
    int size;
public:
    struct Node
    {
        T1 data1;
        T2 data2;
        Node() : data1(T1()), data2(T2()) {}   //deafult constructor for node
        Node(T1 x, T2 y) : data1(x), data2(y) {}  //member initializer list node
    };
    Node* nodes;   // array for storing data
    Heap()
    {
        nodes = nullptr;
        size = -1;
    }

    Heap(T1 x, T2 y)   // parametrized constructor
    {
        size = -1;
        nodes = new Node[size + 1];
        nodes[0] = Node(x, y);
        size = 0;
    }

    int parent_node(int node)  // to get the parent
    {
        return (node - 1) / 2;  // starting from [0] index
    }

    int leftChild(int node)  // to get the left child
    {
        return ((2 * node) + 1);
    }

    int rightChild(int node) // to get the right child
    {
        return ((2 * node) + 2);
    }

    void shiftUp(int n)  // shift up the heap to maintain the structure of heap
    {
        while ((n > 0) && (nodes[parent_node(n)].data2 < nodes[n].data2))
        {
            swap(nodes[parent_node(n)], nodes[n]);
            n = parent_node(n);
        }
    }

    void shiftDown(int n)  // shift down the heap to maintain the structure of heap
    {
        int maximum_Index = n;
        int l = leftChild(n);

        if (l <= size && nodes[l].data2 > nodes[maximum_Index].data2)
        {
            maximum_Index = l;
        }

        int r = rightChild(n);

        if (r <= size && nodes[r].data2 > nodes[maximum_Index].data2)
        {
            maximum_Index = r;
        }

        if (n != maximum_Index)
        {
            swap(nodes[n], nodes[maximum_Index]);
            shiftDown(maximum_Index);
        }
    }

    bool isEmpty() const  // to check if heap is empty
    {
        return size == -1;
    }

    void insert(T1 x, T2 y)  // inserting new data to heap 
    {
        // create new dynamic array of size one greater from previous , copy data from previous to new array and then delete the new array
        size = size + 1;
        Node* newNodes = new Node[size + 1];
        copy(nodes, nodes + size, newNodes);
        delete[] nodes;
        nodes = newNodes;  // named the new array as nodes
        nodes[size] = Node(x, y);
        shiftUp(size);   // shiftup after inserting new node to maintain heap structure
    }

    Node extract_minimum_value()  // extract minimum value
    {
        if (size == -1)
        {
            cout << "Heap is empty." << endl;
            return Node(T1(), T2()); // Default Node construction for an empty heap
        }

        Node result = nodes[0];  // to return the minimum value from the heap
        nodes[0] = nodes[size];
        size = size - 1;

        Node* newNodes = new Node[size + 1];
        copy(nodes, nodes + size + 1, newNodes);
        delete[] nodes;
        nodes = newNodes;

        shiftDown(0);
        return result;
    }

    Node get_minimum_node()  // get the minimum value from the heap without extracting the minimum value
    {
        if (size == -1)
        {
            cout << "Heap is empty." << endl;
            return Node(T1(), T2()); // Default Node construction for an empty heap
        }

        return nodes[0];
    }


    ~Heap()  // destructor
    {
        delete[] nodes;
    }
};