#include <iostream>
#include <fstream>
#include <string>

int main() 
{
std::ifstream infile("data-4.txt");

//Remove first line
std::string header;
std::getline(infile, header);

//Initialise 1000 array to 0
int degree[1000], temp;
for (int i = 0; i < 1000; i++)
	degree[i] = 0;

//Simple counting
while( !infile.eof() ) {
	infile >> temp;
	if ( infile.eof() ) break;
	degree[temp-1] += 1; 
}

infile.close();

//Print
for (int i = 0; i < 1000; i++)
	std::cout << degree[i] << " "; 
}
