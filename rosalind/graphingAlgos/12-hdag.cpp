#include <iostream>
#include <fstream>
#include "../algos/Graph.cpp"

int main() 
{
	int vertices, edges, graphs, v, e, w;
	std::fstream infile("data-12a.txt");
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
  		}
  
  		// Print graph
		myGraph.display();
		myGraph.HDAG();
	}
	infile.close();
}

