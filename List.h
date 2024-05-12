//Muneeb ur Rehman  22i2702
//Musfirah Zunnoon  22i2692


#pragma once
#include"node.h"
#include <iostream>
using namespace std;

class list  // list for storing nodes
{
public:
    node* head;
    list()
    {
        head = nullptr;
    }

    void addnodes(int n)
    {
        if (head == nullptr)  // if list is empty
        {
            head = new node(n);
            head->next = nullptr;
            return;
        }
        node* curr = head;
        while (curr->next != nullptr)  // else traverse at the end of the list to insert node
        {
            curr = curr->next;
        }
        curr->next = new node(n);
        curr->next->next = NULL;
    }

    void displayList() // display nodes' ids
    {
        node* current = head;
        while (current != nullptr)
        {
            cout << current->id << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~list()  // destructor
    {
        while (head != nullptr)
        {
            node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};