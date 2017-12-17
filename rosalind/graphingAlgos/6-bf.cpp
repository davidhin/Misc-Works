#include <iostream>
#include <fstream>
#include "../algos/Graph.cpp"
#include "../algos/minHeap.cpp"

// Using https://www.youtube.com/watch?v=obWXjtg0L64

int main() 
{
	srand (time(NULL));
	int vertices, edges, v, e, w;
	std::fstream infile("data-6a.txt");
	infile >> vertices >> edges;

	// Initiate graph	
	Graph myGraph(vertices);
	for (int i = 0; i < edges; i++)
	{
		infile >> v >> e >> w;
		myGraph.addEdge(v, e, w);
	}
	infile.close();
	
	// Print graph
	myGraph.display();
	myGraph.BF();
}
