#include <iostream>
#include <fstream>

int binSearch(int* array, int num, int length) {
	int low = 0;
	int high = length;
	int mid = (low + high) / 2;
	while (array[mid] != num && mid != low) {
		if (array[mid] < num)
			low = mid;	
		if (array[mid] > num)
			high = mid;
		mid = (low + high) / 2;
	}
	
	return (array[mid] == num ? num : -1);
}

void massBinSearch(int* searchArray, int* numArray, int searchSize, int numSize) {
	for (int i = 0; i < numSize; i++)
		std::cout << binSearch(searchArray, numArray[i], searchSize) << " ";
	std::cout << std::endl;
}

int main() {
	// Load the txt file
	std::ifstream inputfile;
	inputfile.open("data-2.txt");
	
	// Define array sizes using first two lines
	int aSize1, aSize2;
	inputfile >> aSize1;
	inputfile >> aSize2;
	int* a1 = new int[aSize1];
	int* a2 = new int[aSize2];
	
	// Populate arrays a1 and a2 with numbers in line 3 and line 4
	for (int i = 0; i < aSize1; i++)
		inputfile >> a1[i];
	for (int i = 0; i < aSize2; i++)
		inputfile >> a2[i];

	// End file read
	inputfile.close(); 

	massBinSearch(a1, a2, aSize1, aSize2);
	delete[] a1, a2;
}


/*
int low = 0;
int high = n;
while (array[mid] != num) {
	int mid = (low + high) / 2;
	if (array[mid] < num)
		low = mid;	
	if (array[mid] > num)
		high = mid;
}

if (array[mid] == num) 
	return mid;
else
	return -1;

while num is not equal to searched, 
reduce search space to the correct half of the array
repeat

*/
