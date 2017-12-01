#include <iostream>
#include <fstream>
#include <unordered_map>

int moore(int* array, int length) {
	int m, i, check;
	i = 0;

	for (int j = 0; j < length; j++)
	{
		if (i == 0) { m = array[j]; i = 1; }
		else if ( m == array[j] ) { i++; }
		else { i--; } 
	}

	for (int j = 0; j < length; j++)
	{
		if (array[j] == m) check++;
	}

	if (check > length/2) return m;
	else return -1;
}

int originalSolution(int* array, int length)
{
	std::unordered_map<int, int> counter;
	for (int i = 0; i < length; i++)
	{
		counter[ array[i] ]++;
		if (counter.at( array[i] ) > length/2)
			return array[i];
	}
	return -1;
}


int main() 
{
int k, n;
std::fstream infile("data-5.txt");
infile >> k;
infile >> n;
int* a = new int[n];

for (int i = 0; i < k; i++)
{
	for (int j = 0; j < n; j++) 
	{
		infile >> a[j];
	}
	std::cout << moore(a, n) << " ";
}

infile.close();
}
