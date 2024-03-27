#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <Windows.h>
#include "Graph.h"
using namespace std;


void setColor1(int code) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code);
}

graph::graph(){
	this->GRAPH.resize(7);
	// 0 means Washington DC
	// 1 means New York
	// 2 means Chicago
	// 3 means Detroit
	// 4 means Denver
	// 5 means San Francisco
	// 6 means Los Angeles

	// For Washington DC Vertex
	this->GRAPH[0].push_back({1, 226});	 // To New York
	this->GRAPH[0].push_back({2, 696});	 // To Chicago
	this->GRAPH[0].push_back({3, 520});	 // To Detroit
	this->GRAPH[0].push_back({6, 2668}); // To Los Angeles

	// For New York Vertex
	this->GRAPH[1].push_back({0, 226}); // To Washington DC
	this->GRAPH[1].push_back({2, 790}); // To Chicago
	this->GRAPH[1].push_back({3, 614}); // To Detroit

	// For Chicago Vertex
	this->GRAPH[2].push_back({0, 696});	 // To Washington DC
	this->GRAPH[2].push_back({1, 790});	 // To New York
	this->GRAPH[2].push_back({3, 283});	 // To Detroit
	this->GRAPH[2].push_back({4, 1002}); // To Denver

	// For Detroit Vertex
	this->GRAPH[3].push_back({0, 520});	 // To Washington DC
	this->GRAPH[3].push_back({1, 614});	 // To New York
	this->GRAPH[3].push_back({2, 283});	 // To Chicago
	this->GRAPH[3].push_back({5, 2398}); // To San Francisco

	// For Denver Vertex
	this->GRAPH[4].push_back({2, 1002}); // To Chicago
	this->GRAPH[4].push_back({5, 1252}); // To San Francisco
	this->GRAPH[4].push_back({6, 1016}); // To Los Angeles

	// For San Francisco
	this->GRAPH[5].push_back({3, 2398}); // To Detroit
	this->GRAPH[5].push_back({4, 1252}); // To Denver
	this->GRAPH[5].push_back({6, 382});	 // To Los Angeles

	// For Los Angeles
	this->GRAPH[6].push_back({0, 2668}); // To Washington DC
	this->GRAPH[6].push_back({4, 1016}); // To Denver
	this->GRAPH[6].push_back({5, 382});	 // To San Francisco
}

void graph::breadthFirstSearch(int start){
	const int src = start;
	cout << "Breadth-First Search: " << endl;
	vector<bool> visited(GRAPH.size(), false);
	queue<int> bfsQueue;
	bfsQueue.push(src);
	visited[src] = true;
	while (!bfsQueue.empty())
	{
		int currentVertex = bfsQueue.front();
		bfsQueue.pop();
		cout << nameOfVertices[currentVertex] << endl;
		for (int i = 0; i < GRAPH.size(); ++i)
		{
			if (!visited[i])
			{
				bfsQueue.push(i);
				visited[i] = true;
			}
		}
	}
}

void graph::depthFirstSearch(int start){
	const int src = start;
	cout << "Depth-First Search: " << endl;
	vector<bool> visited(GRAPH.size(), false);
	stack<int> dfsStack;
	dfsStack.push(src);
	visited[src] = true;
	while (!dfsStack.empty())
	{
		int currentVertex = dfsStack.top();
		dfsStack.pop();
		cout << nameOfVertices[currentVertex] << endl;
		for (int i = 0; i < GRAPH.size(); ++i)
		{
			if (!visited[i])
			{
				dfsStack.push(i);
				visited[i] = true;
			}
		}
	}
	cout << "\n";
}

void graph::dijkstraAlgorithm(int source, int destination){
	const int INF = 1e9;
	int numNodes = GRAPH.size();
	vector<int> distance(numNodes, INF);
	vector<bool> visited(numNodes, false);
	vector<int> parent(numNodes, -1);
	distance[source] = 0;
	priority_queue<int, vector<int>, greater<int>> priorityQueue;
	priorityQueue.push(source);
	while (!priorityQueue.empty()){
		int u = priorityQueue.top();
		priorityQueue.pop();
		if (u == destination){
			break;
		}
		if (visited[u]){
			continue;
		}
		visited[u] = true;
		for (const edge &e : GRAPH[u]){
			int v = e.destination;
			int weight = e.weight;
			if (!visited[v] && distance[u] != INF && distance[u] + weight < distance[v]){
				distance[v] = distance[u] + weight;
				priorityQueue.push(v);
				parent[v] = u; 
			}
		}
	}
	if (distance[destination] == INF){
		cout << "No path from ";setColor1(10);cout<< nameOfVertices[source];setColor1(15);cout<< " to " ;setColor1(10);cout<< nameOfVertices[destination] << endl;
	}
	else{
		cout << "Shortest path from ";setColor1(10);cout << nameOfVertices[source] ;setColor1(15);cout<< " to ";setColor1(10); cout<< nameOfVertices[destination] << ":\n\n";
		stack<int> path;
		int current = destination;
		while (current != -1)
		{
			path.push(current);
			current = parent[current];
		}
		setColor1(10);
		cout << "Path: ";
		setColor1(15);
		while (!path.empty())
		{
			cout << nameOfVertices[path.top()] << " ";
			path.pop();
		}
		cout << "\n\nTotal distance ";setColor1(10);cout<<distance[destination]; setColor1(15);cout<<" miles"<< endl<<endl;
	}
}