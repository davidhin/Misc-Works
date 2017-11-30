#include <iostream>
#include <fstream>
#include <random>

void printArr(int* a, int n, int j = -1, int p = -1, int q = -1, int loHl = -1, int red = -1)
{

	for (int i = 0; i < n; i++) 
	{
		if (i == j)
			std::cout << "\033[1;32m" << a[i] << "\033[0m" << " ";
		else if (i == p)
			std::cout << "\033[1;33m" << a[i] << "\033[0m" << " ";
		else if (i == q)
			std::cout << "\033[1;35m" << a[i] << "\033[0m" << " ";
		else if (i == loHl)
			std::cout << "\033[1;36m" << a[i] << "\033[0m" << " ";
		else if (i == red)
			std::cout << "\033[1;31m" << a[i] << "\033[0m" << " ";
		else
			std::cout << a[i] << " ";
	}
			std::cout << std::endl;
}

void swap(int* a, int a1, int a2)
{
	int temp = a[a1];
	a[a1] = a[a2];
	a[a2] = temp;
}

int partition(int* a, int low, int high, int length, int index)
{
	// q is low bound, r is high bound s.t a[0] is >= q and < r
	int q = low, r = low+1, num = a[index];
	swap(a, low, index);
	
	for (int i = low + 1; i < high; i++) 
	{
		if (a[i] == num) 
		{	
	/**/		printArr(a, length, i, q, r);	
			swap(a, i, q + 1); 
			q++;
			r++;
	/**/		printArr(a, length, i, q, r);	
			if (a[i] < num) swap(a, i, r-1);	
		}
		else if (a[i] < num) 
		{
	/**/		printArr(a, length, i, q, r);	
			swap(a, i, r);
			r++;
		} 
	/**/	printArr(a, length, i, q, r);	
	/**/	
	/**/	std::cout << " ----- " << std::endl;
	}

	std::cout << "r:" << r << " " << "q:" << q << std::endl;
	for (int i = low; i <= q; i++)
		swap(a, i, r+low-1 - i);
	printArr(a, length, -1, r, r-(q - low)-2, r-(q - low)-1);
	
	return r - (q - low);
}

int median(int* a, int length, int k) 
{
	int randIndex = rand() % length, med = 0, lo = 0, hi = length; // lo and hi use zero index

//  while (med != k)
//	{
//		randIndex = rand() % hi + lo;
//		k = k - lo;
		randIndex = 1;//rand() % (hi-lo) + lo; // rand uses zero index
		std::cout << "randIndex: " << randIndex << std::endl;
		med = partition(a, lo, hi, length, randIndex);
		std::cout << "med: " << med << std::endl;
//		if (med == k) break;
//		if (med < k) hi = med - 2;
//		if (med > k) lo = med;
//	}

	if (med == k) std::cout << k << "th value: " << a[med-1] << std::endl;

}

int main() 
{
	srand(time(NULL));
	int *array, arrSize, k;
	std::fstream infile("data-16a.txt");
	infile >> arrSize;
	array = new int[arrSize];
	for (int i = 0; i < arrSize; i++)
	infile >> array[i];
	infile >> k;
	infile.close();

	printArr(array,arrSize);
	median(array, arrSize, k);
	
	delete[] array;
}
