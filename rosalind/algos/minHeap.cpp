#pragma once
#include <iostream>
#include <vector>

// Pair where first is node and second is distance
typedef std::vector<std::pair<int, int>> nodeDist;

void swap(nodeDist* a, int a1, int a2)
{
	std::pair<int, int> temp = (*a).at(a1);
	(*a).at(a1) = (*a).at(a2);
	(*a).at(a2) = temp;
}

class MinHeap
{
private:
	nodeDist* heap;

public:
	MinHeap();
	void minHeapify();
	void push_back(std::pair<int, int>);
	void pop_front();
	void display();
	bool empty();

	std::pair<int, int> front();
	~MinHeap() { delete heap; }
};

MinHeap::MinHeap()
{
	heap = new nodeDist;
}

void MinHeap::minHeapify()
{	
	nodeDist* a = heap;
	int n = heap->size();
	for (int i = 2; i <= n; i++)
	{
		while ((*a).at(i - 1).second < (*a).at(i / 2 - 1).second)
		{
			int current = i; 
			int next = i / 2; 
			while ((*a).at(current - 1).second <= (*a).at(next - 1).second)
			{	
				swap(a, current - 1, next - 1);
				current /= 2;
				next /= 2;
				if (next == 0) break;
			}
		}
	}
}

void MinHeap::push_back(std::pair<int, int> num)
{
	nodeDist* a = heap;
	a->push_back(num);
	int i = a->size();
	
	if (i > 1)
	while ((*a).at(i - 1).second < (*a).at(i / 2 - 1).second)
	{
		int current = i; 
		int next = i / 2; 
		while ((*a).at(current - 1).second <= (*a).at(next - 1).second)
		{	
			swap(a, current - 1, next - 1);
			current /= 2;
			next /= 2;
			if (next == 0) break;
		}
	}
}

void MinHeap::pop_front()
{
	nodeDist* a = heap;
	swap(a, 0, a->size()-1);
	a->pop_back();
	int n = a->size();
	int i = 1;
	while (true) 
	{
		if (2*i < n && (*a).at(2*i).second <= (*a).at(2*i - 1).second && (*a).at(i-1).second >= (*a).at(2*i).second)
		{
			swap(a, i - 1, 2*i);	
			i = i*2 + 1;
		}
		else if (2*i - 1 < n && (*a).at(i-1).second >= (*a).at(2*i - 1).second )
		{
			swap(a, i - 1, 2*i - 1);
			i *= 2;
		}
		else break;
	}
}

std::pair<int, int> MinHeap::front()
{
	return heap->at(0);
}

void MinHeap::display()
{
	printHeap(*heap, heap->size());
}

bool MinHeap::empty()
{
	if (heap->size() == 0) return 1;
	return 0;
}

//void swapA(int* a, int a1, int a2)
//{
//	int temp = a[a1];
//	a[a1] = a[a2];
//	a[a2] = temp;
//}
//
//void minHeap(int* a, int n)
//{
//	for (int i = 2; i <= n; i++)
//	{
//		while (a[i - 1] < a[i / 2 - 1])
//		{
//			int current = i; 
//			int next = i / 2; 
//	  		while (a[current - 1] <= a[next - 1])
//	  		{	
//	  			swapA(a, current - 1, next - 1);
//	  			current /= 2;
//	  			next /= 2;
//	  			if (next == 0) break;
//	  		}
//	 	}
//	}
//}
