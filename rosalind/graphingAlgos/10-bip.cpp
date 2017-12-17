#include <iostream>
#include <fstream>
#include "../algos/Graph.cpp"
#include "../algos/minHeap.cpp"

int main() 
{
	int vertices, edges, graphs, v, e, w;
	std::fstream infile("data-10a.txt");
	infile >> graphs;
	
	for (int j = 0; j < graphs; j++)
	{
		infile >> vertices >> edges;

  		// Initiate graph	
 	 	Graph myGraph(vertices);
  	
  		// Add nodes from file
  		for (int i = 0; i < edges; i++)
  		{
  			infile >> v >> e;
  			myGraph.addEdge(v, e);
  			myGraph.addEdge(e, v); // Undirected graph
  		}
  
  		// Print graph
		myGraph.display();
		std::cout << (myGraph.BIP() ?
			 		"\033[1;39mIs bipartite\033[0m\n\n" : 
					"\033[1;39mIs not bipartite\033[0m\n\n");
	}
	infile.close();
}
