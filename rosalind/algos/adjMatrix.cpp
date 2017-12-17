#pragma once
#include <iostream>
#include "printing.cpp"

class AdjMatrix
{
private:
	int vertices;
	int** adj;

public:
	AdjMatrix(int V);
	void addEdge(int v1, int v2);
	void display();
	void sqUtil(int u1, int u2, int v1, int v2, bool* found, int level);
	bool sq(); // Recursive method, bad
	bool sq2(); // Matrix multiplication
	~AdjMatrix() 
	{
		for (int i = 0; i < vertices; i++)
		delete[] adj[i]; 
		delete[] adj; 
	} 
};

/**************************************************************/
/*			             UTILITY                              */
/**************************************************************/

// Constructor
AdjMatrix::AdjMatrix(int V) 
{
	vertices = V;
	adj = new int*[vertices];
	
	// Create adjacency matrix
	for (int i = 0; i < vertices; i++)
		adj[i] = new int[vertices];	

	// Set all entries to zero
	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
			adj[i][j] = 0;
} 

void AdjMatrix::addEdge(int v1, int v2)
{
	adj[v1-1][v2-1] = 1;
}

void AdjMatrix::display()
{
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
			std::cout << adj[i][j] << " "; 
		std::cout << std::endl;
	}
}

/**************************************************************/
/*	       SQUARE IN A GRAPH (recursive method, bad)          */
/**************************************************************/

// u1 and u2 are the original edge
void AdjMatrix::sqUtil(int u1, int u2, int v1, int v2, bool* found, int level = 0)
{
	// If starting edge doesn't exist or past the 4th edge, return
	if (adj[v1][v2] == 0 || level > 4) return;
	// If returned to the starting edge, print the current level (4 = square)
	if (u1 == v1 && u2 == v2 && level != 0)
	{ 
		std::cout << "Cycle: " << level << std::endl; 
		if (level == 4) *found = true; 
		return; 
	}	

	// For all adjacent vertices, recursion
	for (int i = 0; i < vertices; i++)
	{
		if (adj[v2][i] == 1 && i != v1)
		{
			for (int i = 0; i < level; i++) std::cout << "    "; std::cout << "|---"; 
			std::cout << v2+1 << " " << i+1 << " Level: " << level << std::endl;
			sqUtil(u1, u2, v2, i, found, level+1);
			if (*found) return;
		}
	}
}

bool AdjMatrix::sq()
{

	bool* visited = new bool[vertices];
	for (int i = 0; i < vertices; i++)
		visited[i] = false;

	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
		{
			bool* found = new bool;
			*found = false;
			std::cout << i+1 << " " << j+1 << " Level: Start" << std::endl;
			sqUtil(i, j, i, j, found);
			if (*found) return true;
		}	

	return false;
}

/**************************************************************/
/*	       SQUARE IN A GRAPH (Powers of adjMatrix)            */
/**************************************************************/

bool AdjMatrix::sq2()
{
	int sum = 0;

	// Create new temp matrix;
	int** tmpMat = new int*[vertices];
	for (int i = 0; i < vertices; i++)
		tmpMat[i] = new int[vertices];	

	// Matrix multiply
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			sum = 0;
			for (int k = 0; k < vertices; k++)
				sum = sum + adj[i][k] * adj[k][j];
				tmpMat[i][j] = sum;
		}
	}

	// Display multiplied matrix;
	std::cout << std::endl;	
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			bool colour = false;
			if (i != j && tmpMat[i][j] >= 2) colour = true;
			std::cout << (colour ? "\033[1;36m" : "") 
					  << tmpMat[i][j] << (colour ? "\033[0m" : "") <<" "; 
		}
		std::cout << std::endl;
	}

	// Use properties of powers of adjacency matrix
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			if (i == j) continue;
			if (tmpMat[i][j] >= 2) 
			{
				for (int i = 0; i < vertices; i++)
					delete[] tmpMat[i];
				delete[] tmpMat;
				return true;
			} 
		}
	}

	// Delete matrix	
	for (int i = 0; i < vertices; i++)
		delete[] tmpMat[i];
	delete[] tmpMat;
	return false;
}
