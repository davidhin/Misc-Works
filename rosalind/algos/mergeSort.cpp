#include <iostream>
#include <fstream>

void merge(int* a, int low, int mid, int high)
{
    int left = low, right = mid+1, pos = 0, *temp = new int[high - low + 1];
	
	while (left <= mid && right <= high)
	{
		if (a[left] <= a[right])
		{
			temp[pos] = a[left];
			left++;
			pos++;
		} 
		else
		{
			temp[pos] = a[right];
			right++;
			pos++;
		}
	}

	while (left <= mid)
	{
		temp[pos] = a[left];
		left++;
		pos++;
	}

	while (right <= high)
	{
		temp[pos] = a[right];
		right++;
		pos++;
	}

	for (int i = 0; i <= high - low; i++)
	a[low + i] = temp[i];
	
	delete[] temp;
}

void mergeSort(int* a, int low, int high)
{
	if (low == high) return;
	int mid = (high + low) / 2;
	mergeSort(a, low, mid);
	mergeSort(a, mid+1, high);
	merge(a, low, mid, high);
}
