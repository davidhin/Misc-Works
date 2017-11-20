#include <iostream>

int fibo(int digit, int prev1 = 0, int prev2 = 1) { 
	if (digit == 0) 
		return 0;
	if (digit == 1)
		return 1;
	if (digit == 2)
		return prev1 + prev2;
	fibo(digit - 1, prev2, prev1 + prev2);	
}

int main() {
	for (int i = 0; i < 30; i++) {	
		std::cout << fibo(i) << " ";
	}
	std::cout << std::endl;
}	
