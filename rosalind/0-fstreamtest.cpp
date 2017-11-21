#include <iostream>
#include <fstream>

int main() {
// Load the txt file
std::ifstream inputfile;
inputfile.open("test.txt");

// Define array sizes using first two lines
int aSize1, aSize2;
inputfile >> aSize1;
inputfile >> aSize2;

// Populate arrays a1 and a2 with numbers in line 3 and line 4
int* a1 = new int[aSize1];
int* a2 = new int[aSize2];

for (int i = 0; i < aSize1; i++)
	inputfile >> a1[i];

delete[] a1, a2;
inputfile.close(); 
}
