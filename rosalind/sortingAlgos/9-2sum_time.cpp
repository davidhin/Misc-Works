#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

int main()
{
	int numberOfArrays, arraySize, *arrayOriginal, *array;
	std::fstream infile("data-9.txt");
	infile >> numberOfArrays >> arraySize;
	array = new int[arraySize];
	std::unordered_map<int, int> arrayMap;
	
	for (int i = 0; i < numberOfArrays; i++)
	{
		// Initiate array
		for (int j = 0; j < arraySize; j++)
			infile >> array[j];

		// Add array elements to unordered map and check if value has been added	
		for (int j = 0; j < arraySize; j++)
		{
			// Search map for -ve of the jth element of the array
			std::unordered_map<int, int>::const_iterator got = arrayMap.find(-array[j]);
			
			// If a pair is found, cout and break; else, print -1
			if (!(got == arrayMap.end()))
			{
				if (j+1 < got->second+1) std::cout << j+1 << " " << got->second+1 << std::endl;
				else std::cout << got->second+1 << " " << j+1 << std::endl;
				break;
			} 
			else if (j == arraySize - 1) std::cout << -1 << std::endl; 
			
			// Add curent value to array
			arrayMap[array[j]] = j;	
		}
	
//	std::unordered_map<int,int>::iterator it = arrayMap.begin();
// 	for (it=arrayMap.begin(); it!=arrayMap.end(); ++it)
// 	std::cout << it->first << "|" << it->second << " ";
//	std::cout << std::endl;
	arrayMap.clear();
	}

	infile.close();
	delete[] array;
}
