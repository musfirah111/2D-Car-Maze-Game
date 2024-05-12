//Muneeb ur Rehman  22i2702
//Musfirah Zunnoon  22i2692


#include<iostream>
#include<string>
#pragma once
#include<iostream>
#include<string>
#include<random>
#include<cstdlib>
#include<conio.h>
using namespace std;

class node  //for storing data of nodes of graph
{
public:
    int id;
    int node_cost;
    node* next;
    node(int ids)  // to set the id of nodes
    {
        id = ids;
        node_cost = 1;
        next = NULL;
    }
};

