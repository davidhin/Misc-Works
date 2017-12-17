#include <iostream>
#include <fstream>
#include "../algos/Graph.cpp"
#include "../algos/minHeap.cpp"

// There may have been something wrong with my Bellman-Ford implementation
// Because I could not run the program on the whole dataset given by Rosalind *in one go*.
// I had to split it up into multiple runs using
// if j>=low && j<=high
// Use of memory is probably wrong but can't find the error in Graph.cpp -> BF()

int main() 
{
	srand (time(NULL));
	int vertices, edges, graphs, v, e, w;
	std::fstream infile("data-7a.txt");
	infile >> graphs;
	
	for (int j = 0; j < graphs; j++)
	{
		infile >> vertices >> edges;
		vertices++;	

	  	// Initiate graph	
  		Graph myGraph(vertices);
  	
  		// Dummy source node has weight 0 to all nodes
		for (int i = 2; i <= vertices; i++)
			myGraph.addEdge(1, i, 0);
  	
  		// Add nodes from file
 	 	for (int i = 0; i < edges; i++)
 	 	{
 	 		infile >> v >> e >> w;
			v++; e++;
	  		myGraph.addEdge(v, e, w);
	  	}
  
  		// Print graph
		myGraph.display();
//		if (j == 18)
		std::cout << myGraph.BF() << " \n";
	}

	std::cout << std::endl;
	infile.close();
	
}
