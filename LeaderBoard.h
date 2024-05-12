//Muneeb ur Rehman  22i2702
//Musfirah Zunnoon  22i2692


#pragma once
#include "Max_heap.h"
#include "stack.h"
#include <iomanip>
using namespace std;

class Leaderboard
{
private:
    MaxHeap<string, int> maxHeap; // T1 is the player's name, T2 is the player's score
    const int leaderboardSize;    //to declare number of players to be shown in leaderboard

public:
    Leaderboard(int size) : leaderboardSize(size) {}  //initializer list ti initialize leaderboard size

    void insertScore(const string& playerName, int score)  //funtion to insert score into the heap(maximum priority queue)
    {
        maxHeap.insert(playerName, score);
        if (maxHeap.getSize() > leaderboardSize)
        {
            maxHeap.extract_maximum_value(); // Remove the lowest score if the size exceeds the limit
        }
    }

    void displayLeaderboard()   //display function for leaderboard
    {
        cout << "Rank" << setw(20) << "Name" << setw(15) << "Score" << endl;

        Stack leaderboardStack;  //to store data extract from the heap onto the stack to print data in descending order

        while (!maxHeap.isEmpty())  //keep extracting data from heap until it empties
        {
            MaxHeap<string, int>::Node node = maxHeap.extract_maximum_value();
            leaderboardStack.Push(node.data2); // Push the score onto the stack
            cout << setw(4) << leaderboardStack.get_size() << setw(20) << node.data1 << setw(15) << node.data2 << endl;
        }

        // Pop and display data from the stack
        while (!leaderboardStack.isEmpty())
        {
            int score = leaderboardStack.Top();
            leaderboardStack.Pop();
        }
    }
};