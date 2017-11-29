#include <iostream>
#include <fstream>

void printArr(int* a, int n, int j = -1, int p = -1, int q = -1)
{

	for (int i = 0; i < n; i++) 
	{
		if (i == j)
			std::cout << "\033[1;32m" << a[i] << "\033[0m" << " ";
		else if (i == p)
			std::cout << "\033[1;33m" << a[i] << "\033[0m" << " ";
		else if (i == q)
			std::cout << "\033[1;35m" << a[i] << "\033[0m" << " ";
		else
			std::cout << a[i] << " ";
	}
			std::cout << std::endl;
}

void swap(int* a, int a1, int a2)
{
	int temp = a[a1];
	a[a1] = a[a2];
	a[a2] = temp;
}

void partition(int* a, int length, int index)
{
	// q is low bound, r is high bound s.t a[0] is >= q and < r
	int q = 0, r = 1, num = a[index];
	swap(a, 0, index);
	
	for (int i = 1; i < length; i++) 
	{
		if (a[i] == num) 
		{	
	/**/		printArr(a, length, i, q, r);	
			swap(a, i, q + 1); 
			q++;
			r++;
	/**/		printArr(a, length, i, q, r);	
			if (a[i] < num) swap(a, i, r-1);	
		}
		else if (a[i] < num) 
		{
	/**/		printArr(a, length, i, q, r);	
			swap(a, i, r);
			r++;
		} 
	/**/	printArr(a, length, i, q, r);	
	/**/	std::cout << " ----- " << std::endl;
	}

	for (int i = 0; i <= q; i++)
		swap(a, i, r - 1 - i);
}

int main() 
{
	int *array, arrSize;
	std::fstream infile("data-12a.txt");
	infile >> arrSize;
	array = new int[arrSize];
	for (int i = 0; i < arrSize; i++)
	infile >> array[i];

	partition(array, arrSize, 0);	
	printArr(array, arrSize);
	
	delete[] array;
}
