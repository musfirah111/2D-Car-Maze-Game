#pragma once
#include"List.h"
#include <windows.h>
#include"AdjacencyMatrix.h"
#include"Heap.h"
#include"Queue.h"
#include<stack>
#include <ctime>
#include"Stack.h"
#include <chrono>
#include<queue>
#include <mmsystem.h>
using namespace chrono;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
class Graph
{
	int Graphsize;//GraphsSize
	list nodes;
	Queue *shape;//for printing graph
	QueueObs *obstacles;//for obstacles
	QueueObs *Powerups;//for obstacles
	Adjacency** adjecency_matrix;//Adjacency matrix size
	
	int matrixsize;
	int start;
	int base_score;
	int nodes_distance;
	int no_of_obstacles;
	int no_of_power_ups;
	int tele1;
	int tele2;
public:

	Graph(int GS) // to be inserted
	{

		start = 0;
		Graphsize = GS;
		matrixsize = GS * GS;
		obstacles = new QueueObs(matrixsize);//for obstacles score
		Powerups = new QueueObs(matrixsize);//for powerups score
		shape = new Queue(matrixsize);//for printing graph
		
		createAdjacenecyMatrix();
		Adjancency();
		addNodes();

		tele1 = rand() % matrixsize;
		while (!checkConnections(tele1))
		{
			start = rand() % matrixsize;
		}
		tele2 = rand() % matrixsize;
		while (!checkConnections(tele2)||tele1==tele2)
		{
			start = rand() % matrixsize;
		}
	}

	bool checkObstacleNodes(QueueObs obj,int node)// returns true if the node is obstacle
	{
		while (!obj.isEmpty())
		{
			if (!(obj.Top() > matrixsize) && !(obj.Top() < 0))
				if (obj.Top() == node)
					return true;

			obj.pop();
		}

		return false;
	}
	bool checkPowerNodes(QueueObs obj,int node)// returns true if the node is powerup
	{
		while (!obj.isEmpty())
		{
			if (!(obj.Top() > matrixsize) && !(obj.Top() < 0))
				if (obj.Top() == node)
					return true;

			obj.pop();
		}

		return false;
	}
	void addNodes()// adds nodes to the graph and assign obstacles and powerups
	{
		
		for (int x = 0; x < matrixsize; x++)
		{
			nodes.addnodes(x);
			shape->assignQueue(x,obstacles,Powerups);
		}
	}
	bool checkConnections(int id)// return true if the node has atleast one connect
	{
		if (id < 0 || id >= matrixsize)
			return false;

		for (int x = 0; x < matrixsize; x++)
			if (adjecency_matrix[id][x].val)
				return true;

		return false;
	}
	void automovement()// For auto movement of 
	{
		int starting = 0,end=0,Rend=0;
		Stack empty;

		//Prints Graph
		printAuto(-1, -1, empty);

		// starting and ending input validations
		cout << "Enter the starting point" << endl;
		cin>>starting;
		while(!checkConnections(starting))
		{
			cout << "EIther this node has no connections please re-enter the starting point OR" << endl
				<< "And the starting node must be greater than zero and smaller than" << matrixsize << endl;;
			cin >> starting;
		}
		cout << "Enter the ending point" << endl;
		cin>>end;
		while (!checkConnections(end))
		{
			cout << "Either this node has no connections please re-enter the ending point OR" << endl
				<< "And the ending node must be greater than zero and smaller than" << matrixsize << endl;;
			cin >> end;
		}

		// prev stores all the previos nodes of the shortest path
		int* prev = dijkstraShortestPath(starting,end,matrixsize,adjecency_matrix);

		// Implementing stack to get shortest path nodes
		Stack flow;
		flow.Push(end);
		int p =5;
		Rend = end;
		while(p!=starting)
		{
			 p = prev[end];
			 flow.Push(p);
			end = p;
		}
		system("cls");

		// Printing Graph and car movement
		Stack flow2 = flow;;
		system("cls");
		Stack flow3=flow;

		while(!flow.isEmpty())
		{
			flow3 = flow;
			printAuto(flow.Top(),Rend,flow2);
			Sleep(1000);
			flow.Pop();
			if(!flow.isEmpty())
			system("cls");
		}
		delete[] prev;
	}
	void createAdjacenecyMatrix()// initializes adjacency matrix
	{
		adjecency_matrix = new Adjacency * [matrixsize];
		for (int x = 0; x < matrixsize; x++)
			adjecency_matrix[x] = new Adjacency[matrixsize];

		for (int x = 0; x < matrixsize; x++)
			for (int y = 0; y < matrixsize; y++)
				adjecency_matrix[x][y].val = false;
	}

	// Creates relation between the nodes randomly
	void Adjancency()
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(1, 100);
		
		srand(time(NULL));
		for (int x = 0; x < matrixsize; x++)
		{
			int rm = dis(gen),rcost=0;
			if (rm > (rand() % 100))
				if ((x + 1) < matrixsize && (x + 1) % Graphsize != 0) //if the node is not the last node of row
				{
					rcost = rand() % 15;
					adjecency_matrix[x][x + 1].val = true;
					adjecency_matrix[x + 1][x].val = true;
					adjecency_matrix[x][x + 1].cost = rcost;
					adjecency_matrix[x + 1][x].cost = rcost;
				}

			 rm = dis(gen);
			 if (rm > (rand() % 100))
				 if ((x - 1) >= 0 && x % Graphsize != 0)// if the node is first in row
				{
					 rcost = rand() % 15;
					adjecency_matrix[x][x - 1].val = true;
					adjecency_matrix[x - 1][x].val = true;
					adjecency_matrix[x][x - 1].cost = rcost;
					adjecency_matrix[x - 1][x].cost = rcost;
				}

			rm = dis(gen);
			if (rm > 30)
				if ((x - Graphsize) >= 0)// if  node exist in upper row
				{
					rcost = rand() % 15;

					adjecency_matrix[x][x - Graphsize].val = true;
					adjecency_matrix[x - Graphsize][x].val = true;
					adjecency_matrix[x][x - Graphsize].cost = rcost;
					adjecency_matrix[x - Graphsize][x].cost = rcost;
				}

			rm = dis(gen);
			if (rm > 30)
				if ((x + Graphsize) < matrixsize)// if node exists in lower row
				{
					rcost = rand() % 15;
					adjecency_matrix[x][x + Graphsize].val = true;
					adjecency_matrix[x + Graphsize][x].val = true;
					adjecency_matrix[x][x + Graphsize].cost = rcost;
					adjecency_matrix[x + Graphsize][x].cost = rcost;
				}
		}

	}

	// Algorthm to find shortest path
	int* dijkstraShortestPath(int source_vertex, int destination_vertex, int matrixsize, Adjacency** adjecency_matrix) 
	{
		int* distance = new int[matrixsize];
		bool* visited_vertices = new bool[matrixsize];
		int* previous = new int[matrixsize];

		for (int i = 0; i < matrixsize; i++) {
			distance[i] = INT_MAX;
			visited_vertices[i] = false;
			previous[i] = 0;
		}

		distance[source_vertex] = 0;
		Heap<int, int> minimum_priority_queue;

		minimum_priority_queue.insert(source_vertex, 0);

		// Create a list object to store the nodes in the shortest path
		list shortestPathList;
		
		previous[source_vertex] = source_vertex;
		while (!minimum_priority_queue.isEmpty()) {
			Heap<int, int>::Node h = minimum_priority_queue.extract_minimum_value();
			int vertex = h.data1;
			int cost = h.data2;

			if (visited_vertices[vertex]) {
				continue;
			}

			visited_vertices[vertex] = true;

			shortestPathList.addnodes(vertex);

			for (int i = 0; i < matrixsize; i++) {
				if (adjecency_matrix[vertex][i].val) {
					int e = i;
					int c = 1; //  the cost of all edges is 1

					if (distance[vertex] + c < distance[e]) {
						{
							distance[e] = distance[vertex] + c;
							previous[i] = vertex;
						}
						minimum_priority_queue.insert(e, distance[e]);
					}
				}
			}
		}
		return previous;
	}

	//For the manual movement of the user
	int Manualmove(int start, int end) 
	{
		auto algo_start = high_resolution_clock::now();// start time

		// initial scores to zero
		base_score = 0;
		nodes_distance = 0;
		no_of_obstacles = 0;
		no_of_power_ups = 0;

		int c = 0,Finalscore=0;
		int Rstart = start;
		printMaze(start,end);
		int* dis = dijkstraShortestPath(start, end, matrixsize, adjecency_matrix);

		// Cars movement
		char p = 0;
		while (c != 'b')
		{
			c = 0;
			
			switch ((c = _getch())) {
			case KEY_UP:
				if ((start - Graphsize) >= 0 && adjecency_matrix[start - Graphsize][start].val
					&& p != 'p')
				{
					start -= Graphsize;
					if (start == tele1)
						start = tele2;
					else if (start == tele2)
						start = tele1;
				}
				break;

			case KEY_DOWN:
				if ((start + Graphsize) < (Graphsize * Graphsize) 
					&& adjecency_matrix[start + Graphsize][start].val && p != 'p')
				{
					start += Graphsize;
					if (start == tele1)
						start = tele2;
					else if (start == tele2)
						start = tele1;
				}
				break;

			case KEY_LEFT:
				if ((start - 1) >= 0 
					&& adjecency_matrix[start - 1][start].val && p != 'p')
				{
					start -= 1;
					if (start == tele1)
						start = tele2;
					else if (start == tele2)
						start = tele1;
				}
				break;

			case KEY_RIGHT:
				if (start != Graphsize - 1)
					if ((start + 1) < (Graphsize * Graphsize) 
						&& adjecency_matrix[start + 1][start].val && p != 'p')
					{
						start += 1;
						if (start == tele1)
							start = tele2;
						else if (start == tele2)
							start = tele1;
					}
				break;

			case 'p':// to pause the game
				cout << "Paused" << endl;;
				p = 'p';
				Sleep(1000);
				break;

			case 'r':// to resume the game
			case 'R':
				cout << "Resumed" << endl;
				Sleep(1000);
				p = 'r';
				break;

			case 'i':// to open the instructions
			case 'I':
				cout << "Press" << endl
					<< "\"p\" to pause" << endl
					<< "\"r\" to resume" << endl
					<< "\"b For home menu" << endl;
				c = _getch();
			}
			
			system("cls");
			cout << "Press \"i\" for instructions" << endl;
			
			printMaze(start,end);

			if (c == 'b')// if pressed b exit
				goto back;
			// updates score
			if (p != 'p')
			{
				no_of_obstacles += checkObstacleNodes(*obstacles, start);
				no_of_power_ups += checkPowerNodes(*Powerups, start);
				nodes_distance++;
			}
			
			// If reached to end
			if (start == end)
			{
				auto algo_stop = high_resolution_clock::now();// ending time
				auto algo_time_duration =
					duration_cast<microseconds>(algo_stop - algo_start);
				double manual_time = algo_time_duration.count() / 1000000.0;

				cout << "Congratulations you are on your destination" << endl;
				Stack flow;
				flow.Push(end);
				int d = 5;
				int Rend = end;

				while (d != Rstart)
				{
					d = dis[Rend];
					flow.Push(d);
					Rend = d;
				}
				Finalscore= Score_calculation(manual_time, flow.get_size());
				break;
			}
		}

		return Finalscore;
	back:
		return 0;
	}

	int Obstacles_score() 
	{
		int obs_score = no_of_obstacles * 5;
		return obs_score;
	}

	int power_ups_score() {
		int pow_score = no_of_power_ups * 5;
		return pow_score;
	}

	int distance_score(int distance) // shortest path covered distance*2
	{
		if (nodes_distance > distance) {
			return nodes_distance;
		}
		else {
			return distance * 2;
		}
	}
	// final score calculation
	int Score_calculation(double time, int distance) {
		int DISTANCE = distance_score(distance);
		int OBSTACLES = Obstacles_score();
		int POWER_UPS = power_ups_score();

		base_score = DISTANCE- OBSTACLES + POWER_UPS + time;
		return base_score;
	}

	// Prints maze for the manual 
	void printMaze(int start,int end)
	{
		Queue curQ = *shape;// Queue containing node type
		node* curr = nodes.head;// list of nodes
		int x = 0;

		while(curr)
		{
			if (x == Graphsize)// if the last column
			{
				x = 0;
				cout << endl;
			}
			
			if (curr->id - Graphsize >= 0&&curr->id%Graphsize==0)//checks vertical connections
			{
				node* vcur = curr;
				for (int y = 0; y < Graphsize; y++)
				{
					if (adjecency_matrix[vcur->id - Graphsize][vcur->id].val)
						cout << "|   ";
					else
						cout << "    ";
					vcur = vcur->next;
				}
				cout << endl;
			}

			if (curr->next != NULL)// for horzontal conncections
			{
				node* nxt = curr->next;
				
				
				if (start==curr->id||end==curr->id||curr->id==tele1||curr->id==tele2)
				{
					if(start==curr->id)
					{
						cout << "C";
						if (adjecency_matrix[curr->id][nxt->id].val)
							cout << "---";
						else
							cout << "   ";
					}
					else if (curr->id == tele1 || curr->id == tele2)
					{
						cout << "0";
						if (adjecency_matrix[curr->id][nxt->id].val)
							cout << "---";
						else
							cout << "   ";
					}
					else
					{
						cout << "E";
						if (adjecency_matrix[curr->id][nxt->id].val)
							cout << "---";
						else
							cout << "   ";
					}
				}
				else if (adjecency_matrix[curr->id][nxt->id].val)
					cout << curQ.Top() << "---";
				else
					cout << curQ.Top() << "   ";
				
			}
			else// last node
			{
				if (start == curr->id || end == curr->id)// if node has car on it or is destination
				{
					if (start == curr->id)
					{
						cout << "C";
					}
					else
					{
						cout << "E";
					}
				}
				else
				{
					if (start == curr->id || end == curr->id)
					{
						if (start == curr->id)
						{
							cout << "C";
						}
						else
						{
							cout << "E";
						}
					}
					else
						cout << curQ.Top();
				}
			}
			curr = curr->next;
			curQ.pop();
			x++;
		}
		cout << endl;
	}
	int get_power_ups() { return no_of_power_ups; }

	//returns true if the node is part of shortest path
	bool checkIfShortest(int id, Stack& flow)
	{
		Stack flow2 = flow;
		while (!flow2.isEmpty())
		{
			if (flow2.Top() == id)
				return true;
			flow2.Pop();
		}
		return false;
		
	}
	//print maze for autogame
	void printAuto(int start,int end, Stack &flow)
	{
		Stack flow2 = flow;
		Queue curQ = *shape;
		node* curr = nodes.head;
		int x = 0;
		while(curr)
		{
			if (x == Graphsize)
			{
				x = 0;
				cout << endl;
			}
			
			if (curr->id - Graphsize >= 0&&curr->id%Graphsize==0)//checks vertical
			{
				node* vcur = curr;
				for (int y = 0; y < Graphsize; y++)
				{
					
					if (adjecency_matrix[vcur->id - Graphsize][vcur->id].val)
					{
						if (checkIfShortest(vcur->id - Graphsize, flow)
							&& checkIfShortest(vcur->id, flow2))
						{
							HANDLE hConsole;
							int col;

							hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
							col = 11;
							FlushConsoleInputBuffer(hConsole);
							SetConsoleTextAttribute(hConsole, col);
							cout << "|   ";
							SetConsoleTextAttribute(hConsole, 15);
							
						}
						else
						{ 
							cout << "|   ";
						}
						
					}
					else
						cout << "    ";
					vcur = vcur->next;
				}
				cout << endl;
			}

			if (curr->next != NULL)//Verticabars
			{
				node* nxt = curr->next;
				
				if (start==curr->id||end==curr->id|| checkIfShortest(curr->id,flow2)&& checkIfShortest(nxt->id, flow2))
				{
					if(start==curr->id)
					{
						cout << "C";
						if (adjecency_matrix[curr->id][nxt->id].val)
						{
							if (checkIfShortest(nxt->id, flow2))// if next nodes os part of shortest path
							{
								HANDLE hConsole;
								int col;

								hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
								col = 11;
								FlushConsoleInputBuffer(hConsole);
								SetConsoleTextAttribute(hConsole, col);
								cout << "---";
								SetConsoleTextAttribute(hConsole, 15);
							}
							else
								cout << "---";
						}
						else
							cout << "   ";
					}
					else if(end == curr->id)
					{
						cout << "E";
						if (adjecency_matrix[curr->id][nxt->id].val)
							cout << "---";
						else
							cout << "   ";
					}
					else
					{
						if (adjecency_matrix[curr->id][nxt->id].val)
						{
								HANDLE hConsole;
								int col;

								hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
								col = 11;
								FlushConsoleInputBuffer(hConsole);
								SetConsoleTextAttribute(hConsole, col);
								cout << "+";
								cout << "---";
								SetConsoleTextAttribute(hConsole, 15);
						}
						else
							cout << "   ";
					}
				}
				else if (adjecency_matrix[curr->id][nxt->id].val)
				{
					if (checkIfShortest(curr->id + Graphsize, flow2) && checkIfShortest(curr->id, flow2))
					{
						HANDLE hConsole;
						int col;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						col = 11;
						FlushConsoleInputBuffer(hConsole);
						SetConsoleTextAttribute(hConsole, col);
						cout << "+";
						SetConsoleTextAttribute(hConsole, 15);
						cout << "---";
					}
					else
					cout << "+" << "---";
				}
				else
				{
					if (checkIfShortest(curr->id + Graphsize, flow2) && checkIfShortest(curr->id, flow2))
					{
						HANDLE hConsole;
						int col;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						col = 11;
						FlushConsoleInputBuffer(hConsole);
						SetConsoleTextAttribute(hConsole, col);
						cout << "+";
						SetConsoleTextAttribute(hConsole, 15);
						cout << "   ";
					}
					else
						cout << "+   ";
				}
			}
			else
			{
				if (start == curr->id || end == curr->id)
				{
					if (start == curr->id)
					{
						cout << "C";
					}
					else
					{
						cout << "E";
					}
				}
				else
				cout << "+";
			}
			curr = curr->next;
			x++;
		}
		cout << endl;
	}
	~Graph()
	{
		delete obstacles;
		delete shape;
		delete Powerups;
	}
};