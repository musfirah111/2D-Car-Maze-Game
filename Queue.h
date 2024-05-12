//Muneeb ur Rehman  22i2702
//Musfirah Zunnoon  22i2692
#pragma once
#include<cstdlib>
#include"ObstaclesQ.h"
class Queue//array based queue
{
	char* id;// stores the nodes type
	int size;// size of queue
	int front;
	int rear;
public:
	Queue(const Queue&obj)// copy constructor
	{
		size = obj.size;
		id = new char[size];
		for (int x = 0; x < size; x++)
			id[x] = obj.id[x];
		front = obj.front;
		rear = obj.rear;
	}
	Queue(int siz)//parametrized constructor
	{
		size = siz;
		id = new char[siz];
		front = -1;
		rear = -1;
	}
	char pop()// pops the first element in the queue
	{
		if (front == rear)
		{
			return NULL;
		}
		char num = id[front];
		id[front] = 0;
		front++;
		return num;
	}
	char Top()// returns the first element of the queue
	{
		if (front != rear)
			return id[front];
	}

	// assigns randomly if the node is powerup or obstacles
	void assignQueue(int x,QueueObs* obstacles, QueueObs* powerups)
	{
		if(front==-1&&rear==-1)
		{
			front = 0; 
			rear = 0;	
			id[rear] = '+';
			rear++;
		}
		else
		{
			int division = rand() % 100;
			if (division > 70 && division < 90)
			{
				id[rear] = '#';
				obstacles->EnQueue(x);
			}
			else if (division > 90)
			{
				id[rear] = '*';
				powerups->EnQueue(x);
			}
			else
				id[rear] = '+';
			rear++;
		}
	}
	~Queue()// destructor
	{
		delete[] id;
	}
};