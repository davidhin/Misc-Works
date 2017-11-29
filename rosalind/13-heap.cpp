#include <iostream>
#include <fstream>
#include <cmath>

void print(int* a, int n, int hl = -1, int hl2 = -1)
{
	for (int i = 0; i < n; i++)
	{
		if (i == hl) 
			std::cout << "\033[1;32m" << a[i] << "\033[0m" << " ";
		else if (i == hl2)
			std::cout << "\033[1;33m" << a[i] << "\033[0m" << " ";
		else std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

void swap(int* a, int a1, int a2)
{
	int temp = a[a1];
	a[a1] = a[a2];
	a[a2] = temp;
}

void maxHeap(int* a, int n)
{
	// Bubble up
	for (int i = 2; i <= n; i++)
	{
		while (a[i - 1] > a[i / 2 - 1])
		{
			int current = i; 
			int next = i / 2; 
	/**/	print(a, n, current - 1, next - 1);
	  		while (a[current - 1] >= a[next - 1])
	  		{	
	/**/		std::cout << " Observe: "; print(a, n, current - 1, next-1);
	  			swap(a, current - 1, next - 1);
	/**/		std::cout << "    Swap: "; print(a, n, current - 1, next-1);
	  			current /= 2;
	  			next /= 2;
	  			if (next == 0) break;
	  		}
	/**/		std::cout << std::endl;
	  }
	/**/		print(a, n, i - 1, i/2 - 1);
	/**/		std::cout << "------" << std::endl;
	}
}

int main()
{
	int arrSize, *array;
	std::fstream infile("data-13a.txt");
	infile >> arrSize;
	array = new int[arrSize];
	for (int i = 0; i < arrSize; i++)
		infile >> array[i];
	infile.close();

	maxHeap(array, arrSize);
	print(array, arrSize);

	delete[] array;
}
