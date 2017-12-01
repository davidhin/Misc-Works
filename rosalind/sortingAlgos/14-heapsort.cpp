#include <iostream>
#include <fstream>
#include <cmath>
#include <random>

void print(int* a, int n, int hl = -1, int hl2 = -1, int hl3 = -1)
{
	for (int i = 0; i < n; i++)
	{
		if (i == hl) 
			std::cout << "\033[1;32m" << a[i] << "\033[0m" << " ";
		else if (i == hl2)
			std::cout << "\033[1;33m" << a[i] << "\033[0m" << " ";
		else if (i == hl3)
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
	for (int i = 2; i <= n; i++)
	{
		while (a[i - 1] > a[i / 2 - 1])
		{
			int current = i; 
			int next = i / 2; 
	  		while (a[current - 1] >= a[next - 1])
	  		{	
	  			swap(a, current - 1, next - 1);
	  			current /= 2;
	  			next /= 2;
	  			if (next == 0) break;
	  		}
	  }
	}
}

void siftDown(int* a, int n)
{
	int i = 1;
	while (true) 
	{
/**/		std::cout << "Sift: ";	print(a, n, i-1, 2*i, 2*i-1);
		if (2*i < n && a[2*i] >= a[2*i - 1] && a[i-1] <= a[2*i])
		{
			swap(a, i - 1, 2*i);	
/**/			std::cout << "      "; print(a, n, 2*i, i - 1, 2*i-1);
			i = i*2 + 1;
		}
		else if (2*i - 1 < n && a[i-1] <= a[2*i - 1] )
		{
			swap(a, i - 1, 2*i - 1);
/**/			std::cout << "      "; print(a, n, 2*i - 1, 2*i, i-1);
			i *= 2;
		}
		else break;
	}
}

void heapSort(int* a, int n)
{	
	for (int i = n - 1; i > 0; i--)
	{
		swap(a, 0, i);
/**/		std::cout << "Swap: "; print(a, n, 0, i);
		siftDown(a, i);
/**/		std::cout << "      "; print(a, n, i);
/**/		std::cout << std::endl;
	}
	print(a, n);
}

int main()
{
	int arrSize, *array;
	std::fstream infile("data-14a.txt");
	infile >> arrSize;
	array = new int[arrSize];
	for (int i = 0; i < arrSize; i++)
	infile >> array[i];
	infile.close();


/**/	std::cout << "Original Array: "; print(array, arrSize);
	maxHeap(array, arrSize);
/**/	std::cout << "MxHp: "; print(array, arrSize);
	heapSort(array, arrSize);

	delete[] array;
}
