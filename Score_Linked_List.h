//Muneeb ur Rehman  22i2702
//Musfirah Zunnoon  22i2692


#include "Collections.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class score_list   // linked list for storing collection data
{
public:
    struct Score_Node
    {
        My_collections collect;  // class that contains data memers of collection items
        Score_Node* next;
        Score_Node()
        {
            next = nullptr;
        }
    };
    Score_Node* head;
    score_list()  //default constructor
    {
        head = nullptr;
    }
    void insert(const My_collections& collection)  // insert new items 
    {
        Score_Node* newNode = new Score_Node;
        newNode->collect = collection;
        if (head == nullptr)   // if list is empty 
        {
            newNode->next = head;
            head = newNode;
        }
        else  //else traverse the list to store the data at the end of list
        {
            Score_Node* current_node = head;
            while (current_node->next != NULL)
            {
                current_node = current_node->next;
            }
            current_node->next = newNode;
        }
    }

    My_collections getLastElement()   // to display the score and name at the start of new game of previous game
    {
        if (head == nullptr)
        {
            return My_collections("-", 0, 0);
        }

        Score_Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        return current->collect;
    }


    void write_List_to_file(const string& file)  //function to write data of linked list into a file
    {
        ofstream write_data(file, ios::app);  // append mode to enter data in file after the last data stored

        if (!write_data.is_open())  // if file is not created
        {
            cout << "error in opening a file... " << file << endl;
            return;
        }

        // If the file is empty, write the header
        write_data.seekp(0, ios::end); // Move to the end to check the file size
        if (write_data.tellp() == 0)
        {
            write_data << "Name" << setw(25) << "Scores" << setw(10) << "Jewels" << endl;
        }

        Score_Node* current = head;
        while (current)  // storing data to file
        {
            write_data << current->collect.getName() << setw(10) << current->collect.getScore() << setw(10) << current->collect.getJewels() << endl;
            current = current->next;
        }

        write_data.close();
    }


    void read_Data(const string& file)  //function for reading the data from the file
    {
        ifstream read_data;
        read_data.open(file);
        if (!read_data.is_open())  //if file is not created
        {
            cout << "error in opening a file... " << file << endl;
            return;
        }

        string Name;
        int Score, Jewels;

        while (read_data >> Name >> Score >> Jewels)  // reading data from file until the end of file
        {
            My_collections value(Name, Score, Jewels);  // storing the data from the file into the my_collections class to get each element as required
            insert(value);
        }
        read_data.close();
    }

    ~score_list()  //destructor
    {
        Score_Node* current = head;
        while (current)
        {
            Score_Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
};