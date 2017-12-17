#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "../algos/list.cpp"

// SOMETHING WHICH DOESN'T REALLY WORK BUT I'M NOT SURE WHY
// WHEN YOU MESS UP AND TRY TO IMPLEMENT BFS USING RECURSION INSTEAD OF QUEUE

void printTree(list* list, int n, int level)
{
	for (int i = 0; i < level; i++)
	std::cout << "    ";
	std::cout << level << "---";
	std::cout <<"\033[1;32m" << n+1 << "\033[0m" ;
	std::cout << "\n";
}

void bfs(list* listIn, int n) 
{
	node* cur = listIn[n].head; // Set start of iterator 'cur'
	if (n == 0)	listIn[n].level = 0; // Base Case
	printTree(listIn, n, listIn[n].level); // Print Tree
	
	while (cur != NULL)
	{
		if (listIn[cur->data-1].level == -1)
			listIn[cur->data-1].level = listIn[n].level + 1;		
		cur = cur->next;
	}
	cur = listIn[n].head;

	while (cur != NULL)
	{
		if (listIn[cur->data-1].level == listIn[n].level + 1)
			bfs(listIn, cur->data-1);
		cur = cur->next;
	}
}

int main() 
{
	srand (time(NULL));
	int vertices, edges, tempVert, tempEdge;
	std::fstream infile("data-3.txt");
	infile >> vertices >> edges;

	list* myList = new list[vertices];

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
	std::cout << "\n";

	// Print final array
	for (int i = 0; i < vertices; i++)
	{
		if (myList[i].level != -1)
		std::cout << "\033[1;36m" << myList[i].level  << "\033[0m ";
		else
		std::cout << myList[i].level << " ";
	}
	std::cout << "\n";

	delete myList;
}
