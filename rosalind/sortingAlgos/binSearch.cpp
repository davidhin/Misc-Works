#include <iostream>

int linSearch(int* array3, int num, int length) {
	for (int i = 0; i <= length; i++) 
	{
		if (array3[i] == 2)
			return i;
		else
			return -1;
	}
}


