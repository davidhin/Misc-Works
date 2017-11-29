#include <iostream>
#include <fstream>
#include <unordered_map>

extern void merge(int* a, int low, int mid, int high);
extern void mergeSort(int* a, int low, int high);

int twosum(std::unordered_map<int, int> arrayMap, int* array, 
		   int arraySize, int numSum, int iterator) 
{
	int result[3];

	// Add array elements to unordered map and check if value has been added	
	for (int i = 0; i < arraySize; i++)
	{
		// Search map for the necessary number 
		std::unordered_map<int, int>::const_iterator got = arrayMap.find(numSum-array[i]);
		
		// If a pair is found, cout and break; else, print -1
		if (got != arrayMap.end() && i != iterator)
		{
			result[0] = iterator+1; result[1] = i+1; result[2] = got->second+1;
			mergeSort(result, 0, 2);
			std::cout << result[0] << " " << result[1] << " " << result[2] << std::endl;
			//std::cout << iterator+1  << " " << i+1 << " " << got->second+1 << std::endl;
			return 1;
			break;
		} 
		else if (i == arraySize - 1) 
		{
			if (iterator == arraySize - 1)
			std::cout << -1 << std::endl; 
			return 0;
		}
	}
}	

int main()
{
	int numberOfArrays, arraySize, *arrayOriginal, *array,*temp, lo, hi;
	std::fstream infile("data-10a.txt");
	infile >> numberOfArrays >> arraySize;
	array = new int[arraySize];
	std::unordered_map<int, int> arrayMap;

	for (int i = 0; i < numberOfArrays; i++)
	{
		// Initiate array
		for (int j = 0; j < arraySize; j++)
		{
			infile >> array[j];
			arrayMap[array[j]] = j;
		}
			
		for (int j = 0; j < arraySize; j++)	
			if (twosum(arrayMap, array, arraySize, -array[j], j) == 1) break;	
	
	arrayMap.clear();
	}

	delete array, temp;
}
