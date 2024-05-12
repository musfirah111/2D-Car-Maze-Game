//Muneeb ur Rehman  22i2702
//Musfirah Zunnoon  22i2692


#pragma once
#include <iostream>
using namespace std;

class Stack
{
private:
    struct Node
    {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}  // member initialer list
    };
    Node* top;  // to get the top element
    size_t no_of_elements;  // to get the size of stack  size_t unsigned integer to store maximum size

public:
    void copyConstruct(Stack& copy)    // manual copy constructor to avoid shallow copy
    {
        if (copy.isEmpty())
            return;
        int num = copy.Top();
        copy.Pop();
        copyConstruct(copy);
        copy.Push(num);
        Push(num);
    }
    Stack() : top(nullptr), no_of_elements(0) {}  //deafult constructor
    Stack(Stack& copy)   // parametrized constructor
    {
        no_of_elements = copy.get_size();
        copyConstruct(copy);
    }

    size_t get_size() const    // to get the size of stack
    {
        return no_of_elements;
    }

    void Push(int x)   //function to push elements onto the stack
    {
        Node* temp = new Node(x);
        if (!temp) {

        }
        else {
            temp->next = top;
            top = temp;
            no_of_elements++;
        }
    }

    void Pop()    // to extract elements from the stack
    {
        if (top == nullptr) {

            return;
        }
        else {
            Node* temp = top;
            top = top->next;
            delete temp;
            no_of_elements--;
        }
    }

    int Top()  // to get the top element from the stack
    {
        if (top == nullptr) {
            return 0;
        }
        else {
            return top->data;
        }
    }

    bool isEmpty() const   // to check if stack is empty or not
    {
        return top == nullptr;
    }

    /*~Stack()
    {
        while (top != nullptr)
        {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }*/
};
