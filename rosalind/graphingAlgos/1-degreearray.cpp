#include <iostream>
#include <fstream>
#include "../algos/list.cpp"

int* double_degree_array(list* listIn, int n) 
{
	int* finalArr = new int[n];

	for (int i = 0; i < n; i++) 
	{
		int doubleDegree = 0;
		node* cur = listIn[i].head, *temp;
		
/**/	std::cout<< "\033[1;36m" << "Node " << i+1 << "\033[0m" << std::endl;
		while (cur != NULL)
		{
			temp = listIn[cur->data-1].head;
/**/		std::cout << cur << "\t" << cur->data << "\t" << cur->next << "\t" 
/**/				  << (cur->next == 0 ? "\t" : "") << "Deg: " <<  temp->degree() << std::endl;
			doubleDegree += temp->degree();
			cur = cur->next;
		}
/**/	std::cout << "\033[1;33m" << "Double degree: " << doubleDegree << "\033[0m" << std::endl;
		finalArr[i] = doubleDegree; 
/**/	std::cout << std::endl;
	}

	return finalArr;
}

int main() 
{
	int vertices, edges, tempVert, tempEdge;
	std::fstream infile("data-1a.txt");
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

	// Print double degree array
	int* array2 = double_degree_array(myList, vertices);
	for (int i = 0; i < vertices; i++)
		std::cout << array2[i] << " ";
	std::cout << std::endl;

	delete myList;
}
