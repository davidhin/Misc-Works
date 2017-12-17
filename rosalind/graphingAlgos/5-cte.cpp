#include <iostream>
#include <fstream>
#include "../algos/Graph.cpp"
#include "../algos/minHeap.cpp"
#include "../algos/printing.cpp"

int main() 
{
	int vertices, edges, graphs, v, e, w;
	std::fstream infile("data-5a.txt");
	infile >> graphs;

	// Used for printing array at end
	int* shortestCycleArray = new int[graphs];

	// firstEdge defines the first edge(node1, node2)
	// first = node1, second = node2
	std::pair<int, int> firstEdge;	
	for (int j = 0; j < graphs; j++)
	{
		// Initiate graph
		infile >> vertices >> edges;
		Graph myGraph(vertices);	
		for (int i = 0; i < edges; i++)
		{
			infile >> v >> e >> w;
			myGraph.addEdge(v, e, w);
			//Extract first edge
			if (i == 0)	{ firstEdge.first = v; firstEdge.second = e; }
		}

		// Print graph
		myGraph.display();
		// Shortest cycle uses Dijkstra to find
		// shortest distance to node1 from node 2
		int shortestCycle = myGraph.DIJ(firstEdge.second, firstEdge.first);
	
		// If node 1 cannot be reached, output -1
		// Else, output this distance + the weight from node 1 to node 2,
        // completing the cycle
		if (shortestCycle == -1) 
			shortestCycleArray[j] = -1;
		else 
			shortestCycleArray[j] = shortestCycle 
									+ myGraph.getWeight(firstEdge.first, firstEdge.second);
	}

	infile.close();
	std::cout << std::endl;
	printArr(shortestCycleArray, graphs);
	delete shortestCycleArray;
}
