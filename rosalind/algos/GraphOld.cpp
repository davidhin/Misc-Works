#pragma once
#include <list>
#include <iostream>
#include "printing.cpp"

void swap(int* a, int a1, int a2)
{
	int temp = a[a1];
	a[a1] = a[a2];
	a[a2] = temp;
}

void minHeap(int* a, int n)
{
	for (int i = 2; i <= n; i++)
	{
		while (a[i - 1] < a[i / 2 - 1])
		{
			int current = i; 
			int next = i / 2; 
	  		while (a[current - 1] <= a[next - 1])
	  		{	
	  			swap(a, current - 1, next - 1);
	  			current /= 2;
	  			next /= 2;
	  			if (next == 0) break;
	  		}
	  }
	}
}

class Graph
{
private:
	int vertices;
	std::list<int>* adj;

public:
	Graph(int V);
	void addEdge(int v, int w);
	void BFS(int s, bool showTree);
	void display();
	~Graph() { delete[] adj; } 
};

Graph::Graph(int verticesIn)
{
	vertices = verticesIn;
	adj = new std::list<int>[vertices];
}

void Graph::addEdge(int v1, int v2)
{
	adj[v1-1].push_back(v2);
}

void Graph::display()
{
	for (int i = 0; i < vertices; i++)
	{
		std::cout << "Node " << i+1 << ": ";	
		printList(adj[i]);
	}
	std::cout << std::endl;
}

void Graph::BFS(int start, bool showTree = 0)
{
	// Create array to hold levels of ith element in adj
	int* levels = new int[vertices], curLevel = 0;
	for (int i = 0; i < vertices; i++)\
		levels[i] = -1;
	
//	for (int i = 0; i < vertices; i++)
//	{
//		if (levels[i] == -1)
//		{	
//			start = i + 1;			
//			curLevel = 0;

			// Create a queue for BFS
			std::list<int> queue;
		
			// Mark the level of the current node and enqueue
			levels[start - 1] = curLevel;
			if (showTree) printTree(start, curLevel);
			queue.push_back(start);
		
			// 'i' will be used to get adjacent vertices of vertex
			std::list<int>::iterator i;
		
			while (!queue.empty())
			{
				start = queue.front();
				curLevel = levels[start-1] + 1;
				queue.pop_front();
		
				// Get all adjacent vertices of start and add to queue 	
				for (i = adj[start-1].begin(); i != adj[start-1].end(); ++i)
				{
					if (levels[*i-1] == -1)
					{	
						levels[*i-1] = curLevel;
						if (showTree) printTree(*i, curLevel);
						queue.push_back(*i);
					}
				}
			}

//		std::cout << "----------\n";
//		}
//	}
	
	if (showTree) std::cout << std::endl;
	for (int i = 0; i < vertices; i++)
		if (levels[i] == -1) std::cout << "\033[1;30m" << levels[i] << "\033[0m "; 
		else std::cout << "\033[1;39m" << levels[i] << "\033[0m ";
	std::cout << std::endl;
}
