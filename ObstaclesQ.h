//Muneeb ur Rehman  22i2702
//Musfirah Zunnoon  22i2692

#pragma once
#include<cstdlib>
class QueueObs//array based queue
{
	int* id;// stores the nodes of the 
	int size;// size of queue
	int front;
	int rear;
public:
	QueueObs(const QueueObs& obj)// copy constructor
	{
		size = obj.size;
		id = new int[size];
		for (int x = 0; x < size; x++)
			id[x] = obj.id[x];
		front = obj.front;
		rear = obj.rear;
	}
	QueueObs(int siz)//parametrized constructor
	{
		size = siz;
		id = new int[siz];
		front = -1;
		rear = -1;
	}

	bool isEmpty()// returns true if queue is empty
	{
		if (front == -1 && rear == -1)
			return true;
		else
			return false;

	}

	int pop()// pops the first element in the queue
	{
		if (front == rear)
		{
			front = -1;
			rear = -1;
			return NULL;			
		}
		int num = id[front];
		id[front] = 0;
		front++;
		return num;
	}

	int Top()// returns the first element of the queue
	{
		if (front != rear)
			return id[front];


	}

	void EnQueue(int ids)// inserts ids with obsticles
	{
		if (front == -1 && rear == -1)
		{
			front = 0;
			rear = 0;
			this->id[rear] = ids;
			rear++;

		}
		else
		{
			id[rear] = ids;
			rear++;
		}
	}

	~QueueObs()// destructor
	{
		delete[] id;
	}
};