#include <iostream>
#include <fstream>
#include <vector>
#include "../algos/list.cpp"

void printNode(node* cur)
{
		std::cout << cur << "\t" << cur->data << "\t" << cur->next << "\t"  << std::endl;
}

void displayNode(list* listIn, int n, int traverse = -1)
{
	std::cout<< "\033[1;36m" << "Node " << n+1 << "\033[0m" << std::endl;

	node* temp = listIn[n].head;

	while (temp != NULL)
	{
		if (temp->data == traverse)
		std::cout << "\033[1;35m" << temp << "\t" << temp->data 
			      << "\t" << temp->next << "\033[0m" << std::endl;
		else if (listIn[temp->data-1].head->visited)
		std::cout << "\033[1;34m" << temp << "\t" << temp->data 
			      << "\t" << temp->next << "\033[0m" << std::endl;
		else
		std::cout << temp << "\t" << temp->data << "\t" << temp->next << std::endl;
		
		temp = temp->next;
	}
	
}

// depth first search
void traverse(list* listIn, int n) 
{
		node* cur = listIn[n].head;
		cur->visited = true;
		displayNode(listIn, n);
	
		while (cur->next != NULL || !listIn[cur->data-1].head->visited)
		{
			while (listIn[cur->data-1].head->visited)
			{
				if (cur->next != NULL)	cur = cur->next;
				else return;
			}
			traverse(listIn, cur->data-1);
		//	displayNode(listIn, n, cur->data);	

			if (cur->next != NULL) cur = cur->next;
		}
}

int main() 
{
	int vertices, edges, tempVert, tempEdge;
	std::fstream infile("data-2a.txt");
	infile >> vertices >> edges;

	list* myList = new list[vertices];

	// Populate adjacency list
	for (int i = 0; i < edges; i++)
	{
		infile >> tempVert >> tempEdge;
		myList[tempVert-1].createNode(tempEdge);		
		myList[tempEdge-1].createNode(tempVert);		
	}
	infile.close();

	for (int i = 0; i < vertices; i++)
	{
		std::cout<< "\033[1;36m" << "Node " << i+1 << "\033[0m" << std::endl;
		myList[i].display();
		std::cout << std::endl;
	}
	std::cout << "--------------------------" << std::endl;

	// traverse adjacency list
	int count = 0;
	for (int i = 0; i < vertices; i++)
	{	
		if (myList[i].head == NULL)
		{	
			count++;	
			std::cout<< "\033[1;36m" << "Node " << i+1 << "\033[0m" << std::endl;
			std::cout << "------- " << std::endl;
		}
		else if (!myList[i].head->visited)
		{
			traverse(myList,i);
			count++;
			std::cout << "------- " << std::endl;
		}
	}

	std::cout << count << std::endl;

	delete myList;

	
}
