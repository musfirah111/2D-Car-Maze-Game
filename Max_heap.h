//Muneeb ur Rehman  22i2702
//Musfirah Zunnoon  22i2692


#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T1, typename T2>
class MaxHeap
{
private:
    int size;  //to get size of heap

public:
    struct Node  //stucture of data members of heap
    {
        T1 data1;
        T2 data2;
        Node() : data1(T1()), data2(T2()) {}    //default constructor for Node
        Node(T1 x, T2 y) : data1(x), data2(y) {} //member initializer list for Node
    };
    Node* nodes;  //array to store heap elements
    MaxHeap()  //default constructor for maxHeap
    {
        nodes = nullptr;
        size = -1;
    }

    MaxHeap(T1 x, T2 y)  //parametrized constructor for maxHeap
    {
        size = -1;
        nodes = new Node[size + 1];
        nodes[0] = Node(x, y);
        size = 0;
    }

    int parent_node(int node)  //function to get the parent node
    {
        return (node - 1) / 2;
    }

    int leftChild(int node)   //function to get the left child of parent
    {
        return ((2 * node) + 1);
    }

    int rightChild(int node)  //function to get the right child of parent
    {
        return ((2 * node) + 2);
    }

    void shiftUp(int n)  //shift up the heap to maintain structure of heap  minimum data element on the top
    {
        while ((n > 0) && (nodes[parent_node(n)].data2 < nodes[n].data2))
        {
            swap(nodes[parent_node(n)], nodes[n]);
            n = parent_node(n);
        }
    }

    void shiftDown(int n)
    {
        int maximum_Index = n;  // Assume the current node has the maximum value
        int l = leftChild(n);   // Calculate the index of the left child
        int r = rightChild(n);  // Calculate the index of the right child

        // Compare the value of the left child with the value of the current maximum
        if (l <= size && nodes[l].data2 > nodes[maximum_Index].data2)
        {
            maximum_Index = l;
        }

        // Compare the value of the right child with the value of the current maximum
        if (r <= size && nodes[r].data2 > nodes[maximum_Index].data2)
        {
            maximum_Index = r;
        }

        // If the current node does not have the maximum value among itself and its children
        if (n != maximum_Index)
        {
            swap(nodes[n], nodes[maximum_Index]);  // Swap the current node with the child having the maximum value
            shiftDown(maximum_Index); // Recursively call shiftDown on the swapped child to continue the process
        }
    }


    bool isEmpty() const   //to check if heap is empty or not
    {
        return size == -1;
    }

    void insert(T1 x, T2 y)   //insert values to heap 
    {
        size = size + 1;
        Node* newNodes = new Node[size + 1];  //create dynamic array with increased size to store new slement
        copy(nodes, nodes + size, newNodes);  //copy elemments from previous array to new array
        delete[] nodes;  //delete previous array
        nodes = newNodes;  // name the new array as nodes
        nodes[size] = Node(x, y);
        shiftUp(size);  //shift up after inserting the new data to maintain the structure
    }

    Node extract_maximum_value()  //function for extracting maximum value from the heap
    {
        if (size == -1)
        {
            cout << "Heap is empty." << endl;
            return Node(T1(), T2()); // Default Node construction for an empty heap
        }

        Node result = nodes[0];  //for returning maximum value
        nodes[0] = nodes[size];  // put the last value on first index
        size = size - 1;         // decreased the size of heap


        //make new array , store previous data and delete the previous array
        Node* newNodes = new Node[size + 1];
        copy(nodes, nodes + size + 1, newNodes);
        delete[] nodes;
        nodes = newNodes;

        shiftDown(0);  // shiftdown to maintain heap structure
        return result;
    }

    Node get_maximum_node()  //without extracting the data get the maximum data
    {
        if (size == -1)
        {
            cout << "Heap is empty." << endl;
            return Node(T1(), T2()); // Default Node construction for an empty heap
        }

        return nodes[0];
    }

    int getSize() const  //to get size of heap
    {
        return size + 1;
    }

    ~MaxHeap()
    {
        delete[] nodes;
    }
};