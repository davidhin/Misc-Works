#include <iostream>
#include <fstream>
#include "../algos/GraphOld.cpp"
#include <random>

int main() 
{
	srand (time(NULL));
	int vertices, edges, v, e;
	std::fstream infile("data-3a.txt");
	infile >> vertices >> edges;

	// Initiate graph	
	Graph myGraph(vertices);
	for (int i = 0; i < edges; i++)
	{
//		v = rand() % (vertices-1) + 1;
//		e = rand() % (vertices-1) + 1;
		infile >> v >> e;
		myGraph.addEdge(v, e);
	}

	// Print graph
	myGraph.display();
	myGraph.BFS(1, 1);

	infile.close();
}
