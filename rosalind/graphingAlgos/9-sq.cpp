#include <iostream>
#include <fstream>
#include "../algos/Graph.cpp"
#include "../algos/adjMatrix.cpp"
#include "../algos/minHeap.cpp"

int main() 
{
	// Initial variables
	int graphs, vertices, edges, v, e, w;
	std::fstream infile("data-9a.txt");
	infile >> graphs;
	int* finalArr = new int[graphs];

	// Initiate matrix
	for (int j = 0; j < graphs; j++)
	{
		infile >> vertices >> edges;
		AdjMatrix matrix(vertices);
		for (int i = 0; i < edges; i++)
		{
			infile >> v >> e;
			matrix.addEdge(v,e);
			matrix.addEdge(e,v); // Undirected graph
		}
		matrix.display();
		std::cout << (matrix.sq2() ? 1 : -1) << " ";
		std::cout << std::endl <<  std::endl;
	}
}
