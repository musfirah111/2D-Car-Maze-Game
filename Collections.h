//Muneeb ur Rehman  22i2702
//Musfirah Zunnoon  22i2692


#pragma once
#include <string>
using namespace std;

class My_collections      //class for containing the data to store in the collection linked list and then to file 
{
private:
    string name;
    int score;
    int jewels;
public:
    My_collections()   //default constructor
    {
        name = "";
        score = jewels = 0;
    }
    My_collections(string name, int score, int jewels) // parametrizedconstructor
    {
        this->name = name;
        this->score = score;
        this->jewels = jewels;
    }


    //getters
    string getName() const
    {
        return name;
    }
    int getScore() const
    {
        return score;
    }
    int getJewels() const
    {
        return jewels;
    }


    //setters
    void setName(string newName)
    {
        name = newName;
    }
    void setScore(int newScore)
    {
        score = newScore;
    }
    void setJewels(int newJewels)
    {
        jewels = newJewels;
    }

    friend istream& operator>>(istream& in, My_collections& collection);  // friend function definition to overload >> for my_collections class
    ~My_collections()
    {

    }
};

istream& operator>>(istream& in, My_collections& collection)  // friend function implemented to overload >> for my_collections class
{
    in >> collection.name >> collection.score >> collection.jewels;
    return in;
}