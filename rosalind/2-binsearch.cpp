#include <iostream>

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
	
	if (array[mid] == num) 
		return mid + 1;
	else
		return -1;
}

void massBinSearch(int* searchArray, int* numArray, int searchSize, int numSize) {
	for (int i = 0; i < numSize; i++)
		std::cout << binSearch(searchArray, numArray[i], searchSize) << " ";
	std::cout << std::endl;
}

int main() {
	int mySearchArr[5] = { 10,20,30,40,50 };
	int myNumsArr[6]  = { 40,10,35,14,40,20 };
	massBinSearch(mySearchArr, myNumsArr, 5, 6);
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
