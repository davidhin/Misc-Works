#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "../algos/list.cpp"

int* finalArr;

void bfs(list* listIn, int n, int level = 0) 
{
	node* cur = listIn[n].head;
//	std::cout << "Current Node: " << n+1 << " Level: " << level << std::endl;
	
	for (int i = 0; i < level; i++)
	std::cout << "    ";
	std::cout << level << "---";
	std::cout <<"\033[1;32m" << n+1 << "\033[0m" ;
	std::cout << "\n";

	finalArr[n] = level;

	if (n == 0)	
	{
//		std::cout << "Seen node 1\n";
		listIn[n].visited = true;
	}
	listIn[n].pointed = true;
//	std::cout << "Pointed at node " << n+1 << std::endl;

	bool hasChildren = 0;
	while (cur != NULL)
	{
		if (!listIn[cur->data-1].visited) 
		{	
			hasChildren = 1;
			listIn[cur->data-1].visited = true;		
//			std::cout << "Seen node " << cur->data << "\n";
		}
		cur = cur->next;
	}
	cur = listIn[n].head;

	if (hasChildren)	
	while (cur != NULL)
	{
		if (!listIn[cur->data-1].pointed)
		{
//		std::cout << "TRANSFER " << "FROM " << n+1 << " TO " << cur->data << "\n\n";
			level += 1;
			bfs(listIn, cur->data-1, level);
			level--;
		}	
		cur = cur->next;
	}
}

int main() 
{
	srand (time(NULL));
	int vertices, edges, tempVert, tempEdge;
	std::fstream infile("data-3a.txt");
	infile >> vertices >> edges;

	list* myList = new list[vertices];
	finalArr = new int[vertices];
	for (int i = 0; i < vertices; i++)
		finalArr[i] = -1;
	finalArr[0] = 0;

	// Populate adjacency list
	for (int i = 0; i < edges; i++)
	{
//		tempVert = rand() % (vertices) + 1;
//		tempEdge = rand() % (vertices) + 1;
		infile >> tempVert >> tempEdge;
		myList[tempVert-1].createNode(tempEdge);		
	}
	infile.close();

	// Initial Display
	for (int i = 0; i < vertices; i++)
	{
		std::cout<< "\033[1;36m" << "Node " << i+1 << "\033[0m" << std::endl;
			myList[i].display();
	}
	std::cout << "\n--------------------------\n" << std::endl;
	
	// Perform breadth first search 
	bfs(myList, 0);

	// Print final array
	std::cout << "\n";
	for (int i = 0; i < vertices; i++)
	{
		if (finalArr[i] != -1)
		std::cout << "\033[1;36m" << finalArr[i] << "\033[0m ";
		else
		std::cout << finalArr[i] << " ";
	}
	std::cout << std::endl;	
 
	delete myList;
	delete[] finalArr;
}
