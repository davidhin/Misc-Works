#pragma once

#include "Edge.cpp"
#include <cmath>
#include <vector>

typedef std::vector<std::pair<int, int>> nodeDist;

void printHeap(nodeDist a, int n, int itr = 1)
{
	if (itr > n) return;
	int space = log2(itr);
	for (int i = 0; i < space; i++)
	std::cout << "    ";
	std::cout << "|---";
	std::cout << "\033[1;34m" << a.at(itr-1).second << "\033[0m\033[1;32m(" << a.at(itr-1).first << ")\033[0m" << std::endl;

	printHeap(a, n, itr*2);
	printHeap(a, n, itr*2 + 1);
}

void printList(std::list<int> listIn)
{
	for (auto v : listIn)
		std::cout << v << " ";
	std::cout << std::endl;
}

void printListW(std::list<Edge> listIn)
{
	for (auto v : listIn)
	{
		std::cout << "\033[1;32m" << v.toNode << "\033[0m(\033[1;34m" << v.weight << "\033[0m) ";
	}
	std::cout << std::endl;
}

void printTree(int n, int level, int weight = 0)
{
	for (int i = 0; i < level; i++)
	std::cout << "      ";
	std::cout << level << "--\033[1;34m" << weight <<"\033[0m--";
	std::cout <<"\033[1;32m" << n << "\033[0m" ;
	std::cout << "\n";
}

void printArr2(int* a, int n, int num)
{
	for (int i = 0; i < n; i++)
		if (a[i] == num) std::cout << "\033[1;36m" << a[i] <<"\033[0m ";
		else std::cout << a[i] << " ";
	std::cout << std::endl;
}

void printArr(int* a, int n, int* hl = NULL)
{
	if (hl != NULL)
	{	
		for (int i = 0; i < n; i++)
			if (hl[i] == 1) std::cout << "\033[1;36m" << a[i] << "\033[0m ";
			else std::cout << a[i] << " ";
	}
	else
	{
		for (int i = 0; i < n; i++)
			if (a[i] == -1) std::cout << "-1 "; 
			else std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

int* hlArray(int n)
{
	int* temp = new int[n];
	for (int i = 0; i < n; i++)
		temp[i] = 0;
	return temp;
}
