#include <iostream>
#include <fstream>

int* mergeSortedArrays(int* a1, int n1, int*a2, int n2) 
{
	int left = 0, right = 0, i = 0;
	int* temp = new int[n1 + n2];
	
	while (left < n1 && right < n2)
	{
		if (a1[left] < a2[right]) 
		{
			temp[i] = a1[left];
			left++;
		} 
		else 
		{
			temp[i] = a2[right];
			right++;	
		}
		i++;
	}
	
	while (left == n1 && right < n2)
	{
		temp[i] = a2[right];
		right++;
		i++;
	}
	
	while (right == n2 && left < n1)
	{
		temp[i] = a1[left];
		left++;
		i++;
	}
	
	for (int i = 0; i < n1+n2; i++)
		std::cout << temp[i] << " ";
	return temp;
}

int main() 
{
	int a1Size, a2Size, *a1, *a2, *finalArray;
	std::fstream infile("data-6.txt");
	
	infile >> a1Size;
	a1 = new int[a1Size];
	for (int i = 0; i < a1Size; i++) 
		infile >> a1[i];
	
	infile >> a2Size;
	a2 = new int[a2Size];
	for (int i = 0; i < a2Size; i++)
		infile >> a2[i];
	
	infile.close();
	
	mergeSortedArrays(a1, a1Size, a2, a2Size);
	delete[] a1, a2;
}
