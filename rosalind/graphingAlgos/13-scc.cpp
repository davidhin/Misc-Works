#include <iostream>
#include <fstream>
#include "../algos/Graph.cpp"
#include "../algos/minHeap.cpp"

int main() 
{
	int vertices, edges, v, e;

	std::fstream infile("data-13a.txt");
	infile >> vertices >> edges;

	// Initiate graph	
	Graph myGraph(vertices);
	for (int i = 0; i < edges; i++)
	{
		infile >> v >> e;
		myGraph.addEdge(v, e);
	}
	infile.close();
	
	// Print graph
	myGraph.display();
	myGraph.SCC();
}

