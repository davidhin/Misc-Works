#include <iostream>
#include <fstream>

void printArr(int* a, int n)
{
	for (int i = 0; i < n; i++)
		std::cout << a[i] << " ";
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
	int lowBound = 1, num = a[index];
	swap(a, 0, index);
	
	for (int i = 1; i < length; i++) 
	{
		if (a[i] <= num) 
		{	
			swap(a, i, lowBound); 
			lowBound++;	
		}
	//	printArr(a, length);	
	}
	swap(a, 0, lowBound - 1);	
}

int main() 
{
	int *array, arrSize;
	std::fstream infile("data-11a.txt");
	infile >> arrSize;
	array = new int[arrSize];
	for (int i = 0; i < arrSize; i++)
	infile >> array[i];

	for (int i = 0; i < arrSize; i++)
	partition(array, arrSize, i);
	
	
	printArr(array, arrSize);
	
	delete[] array;
}
