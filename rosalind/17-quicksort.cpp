#include <iostream>
#include <fstream>
#include <random>

int* done, *done2;

void printArr(int* a, int n, int j = -1, int p = -1, int q = -1, int loHl = -1, int hiHL = -1, int* red = 0, int* cyanDone = 0)
{
	if (red != 0)
	{
		for (int i = 0; i < n; i++)
		{
			if (cyanDone[i] == 1)                                        		
			std::cout << "\033[1;36m" << a[i] << "\033[0m" << " ";    
			else if (red[i] == 1)
			std::cout << "\033[1;37m" << a[i] << "\033[0m" << " ";
			else
			std::cout << "\033[1;30m" << a[i] << "\033[0m" << " ";
		}		
		std::cout << std::endl;
		return;
	}

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
		else if (i == hiHL)
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

// Create a 3-partition
int partition(int* a, int low, int high, int length, int index)
{
	// q is low bound, r is high bound s.t a[0] is >= q and < r
	int q = low, r = low+1, num = a[index];
	swap(a, low, index);
	
	for (int i = low + 1; i < high; i++) 
	{
		if (a[i] == num) 
		{	
	std::cout << "Partition:    ";	
	/**/		printArr(a, length, i, q, r);	
			swap(a, i, q + 1); 
			q++;
			r++;
	std::cout << "Partition:    ";	
	/**/		printArr(a, length, i, q, r);	
			if (a[i] < num) swap(a, i, r-1);	
		}
		else if (a[i] < num) 
		{
	std::cout << "Partition:    ";	
	/**/		printArr(a, length, i, q, r);	
			swap(a, i, r);
			r++;
		} 
	std::cout << "Partition:    ";	
	/**/	printArr(a, length, i, q, r);	
	}

	//std::cout << "r:" << r << " " << "q:" << q << std::endl;
	if (a[0] <= a[r] || r >= length) // Swap a[r] or not
		for (int i = low; i <= q; i++)
			swap(a, i, r + low - i - 1);
	else
		for (int i = low; i <= q; i++) 
			swap(a, i, r + low - i);
	
	std::cout << "Swap:         ";	
	//printArr(a, length, -1, r, r-(q - low)-2, r-(q - low)-1);
	for (int i = low; i <= q; i++)
	{
		done[r-(q-low)-1 + i - low] = 1;	
		done2[r-(q-low)-1 + i - low] = 1;
	}
	printArr(a, length, -1, -1,-1, -1, -1, done, done2);	
	for (int i = 0; i < length; i++)
		done2[i] = 0;
	
	return r - (q - low);
}

void quickSort(int* a, int lo, int hi, int length)
{
	if (hi - lo == 0) return;

	int pivot = random() % (hi-lo) + lo;
/**/	std::cout << "Choose Pivot: ";	printArr(a, length,-1,pivot);
	int newPos = partition(a, lo, hi, length, pivot);	
	std::cout << std::endl;


	pivot = random() % (hi-lo) + lo + 1;
	quickSort(a, lo, newPos-1, length);

	while (a[newPos] == a[newPos - 1]) newPos++;
	quickSort(a, newPos, hi, length);
}

int main() 
{
	srand(time(NULL));
	int *array, arrSize;
	std::fstream infile("data-17a.txt");
	infile >> arrSize;
	array = new int[arrSize];
	done = new int[arrSize];
	done2 = new int[arrSize];
	for (int i = 0; i < arrSize; i++)
	//array[i] = rand() % 99 + 1;
	
	infile >> array[i];
	infile.close();
	
	quickSort(array, 0, arrSize, arrSize);
	std::cout << "SORTED:       "; printArr(array, arrSize);
	
	delete[] array, done, done2;
}
