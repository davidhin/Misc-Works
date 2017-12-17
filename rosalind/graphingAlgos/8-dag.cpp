#include <iostream>
#include <fstream>
#include "../algos/Graph.cpp"
#include "../algos/minHeap.cpp"

int main() 
{
	int graphs, vertices, edges, v, e, w;
	std::fstream infile("data-8a.txt");
	infile >> graphs;
	int* finalArr = new int[graphs];
	
	for (int j = 0; j < graphs; j++)
	{	
		// Initiate graph	
		infile >> vertices >> edges;
		Graph myGraph(vertices);
		for (int i = 0; i < edges; i++)
		{
			infile >> v >> e;
			myGraph.addEdge(v, e);
		}
		myGraph.display();
		finalArr[j] = ((myGraph.DAG() == true) ? 1 : -1);
		std::cout << std::endl;
	}

	printArr(finalArr, graphs);

	infile.close();
	delete[] finalArr;
}
