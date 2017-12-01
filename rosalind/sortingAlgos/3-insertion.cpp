#include <iostream>
#include <fstream>

void swap(int* a, int pos1, int pos2)
{
	int temp = a[pos2];
	a[pos2] = a[pos1];
	a[pos1] = temp;
}

void printArr(int* a, int n) 
{
	for (int i = 0; i < n; i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;
}

int isort(int* a, int length)
{
int count = 0;
	for (int i = 1; i < length; i++) 
	{
		for (int j = i-1; j >= 0 && a[j] > a[j+1]; j--) 
		{
			swap(a, j, j+1);
			count++;
		}
	}
return count;
}

int main() 
{
	std::fstream infile;
	infile.open("data-3.txt");
	int size;
	infile >> size;
	int* nums = new int[size];
	for (int i = 0; i < size; i++) 
		infile >> nums[i];

	std::cout << isort(nums, size) << std::endl;
	delete[] nums;
}
