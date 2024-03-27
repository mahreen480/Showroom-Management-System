#ifndef Graph
#define Graph

#include <vector>


struct edge{
	int destination;
	int weight;
};

class graph {
public:
	graph();
	void breadthFirstSearch(int = 0);
	void depthFirstSearch(int = 0);
	void dijkstraAlgorithm(int,int);
private:
	std::vector<std::vector<edge>> GRAPH;
	// 0 means Washington DC
	// 1 means New York
	// 2 means Chicago
	// 3 means Detroit
	// 4 means Denver
	// 5 means San Francisco
	// 6 means Los Angeles
	std::vector<std::string> nameOfVertices = {"Washington-DC","New-York", "Chicago","Detroit","Denver","San-Francisco","Los-Angeles"};
};

#endif 
