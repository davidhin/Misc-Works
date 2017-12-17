#include <iostream>
#include <fstream>
#include <list>
#include "../algos/Graph.cpp"
#include "../algos/minHeap.cpp"

int main() 
{
	int graphs, vertices, edges, v, e, w;
	std::fstream infile("data-11a.txt");
	
	// Initiate graph	
	infile >> vertices >> edges;
	Graph myGraph(vertices);
	for (int i = 0; i < edges; i++)
	{
		infile >> v >> e;
		myGraph.addEdge(v, e);
	}
	myGraph.display();
	myGraph.TS();

	infile.close();
}
