#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

extern void merge(int* a, int low, int mid, int high);
extern void mergeSort(int* a, int low, int high);

int main()
{
	int numberOfArrays, arraySize, *arrayOriginal, *array,*temp, lo, hi;
	std::fstream infile("data-10a.txt");
	infile >> numberOfArrays >> arraySize;
	array = new int[arraySize];
	temp = new int[arraySize];
	std::unordered_map<int, int> arrayMap;
	
	for (int i = 0; i < numberOfArrays; i++)
	{
		// Initiate array
		for (int j = 0; j < arraySize; j++)
		{
			infile >> array[j];
			temp[j] = array[j];
		}

		// Sort temp array
		mergeSort(temp, 0, arraySize-1);

		// Add array to unordered map; key is arrayValue, value is arrayIndex
		for (int j = 0; j < arraySize; j++)
			arrayMap[temp[j]] = j;	

		// keep track of which 2 values in array are looked at
		lo = 0; hi = arraySize-1;
		std::unordered_map<int, int>::const_iterator got = arrayMap.find(-(temp[lo]+temp[hi]));		

		// Back and forth while loop to find 3rd element that adds to 0
		while (got == arrayMap.end() || got->second == lo || got->second == hi) 
		{
			if (temp[lo] + temp[hi] >= 0)
			{
				if (temp[hi-1] > 0) hi--;
				else if (temp[lo + 1] < 0) lo++;
			}
			else if (temp[lo] + temp[hi] < 0)
			{
				
			}
	
			if (lo == hi) break;
			got = arrayMap.find(-(temp[lo]+temp[hi]));
		}
		
		// Final print
		if (lo != hi) 
		{
			int num[3];

			for (int j = 0; j < arraySize; j++) 
			{
				if (array[j] == temp[lo]) { num[0] = j; temp[lo] = 1000000; }
				else if (array[j] == temp[got->second]) { num[1] = j;  temp[got->second] = 1000000; }
				else if (array[j] == temp[hi]) { num[2] = j; temp[hi] = 1000000; }
			}
			// Inefficient ordering of indices
			mergeSort(num, 0, 2);
			std::cout << num[0] + 1 << " " << num[1] + 1 << " " << num[2] + 1 << std::endl;
		//	std::cout << lo << " " << got->second << " " << hi << std::endl;
		}
		if (lo == hi)
			std::cout << -1 << std::endl;
		arrayMap.clear();
	}

	infile.close();
	delete[] array, temp;
}
