#include "../src/ingredient.h"
#include "../src/plant.h"
#include "../src/mineral.h"
#include "../src/other.h"
#include "../src/mix.h"

#include <iostream>
#include <string>
#include <time.h>

typedef std::unordered_map<std::string, ingredient*> ingredientMap;

int main() {
	plant myPlant = plant("flower");
	for (int i = 0; i < 6; i++)
		std::cout << myPlant.enabledProcesses[i] << " ";
		std::cout << std::endl;
	myPlant.showProcesses();

	std::unordered_map<int, std::string>::iterator it = myPlant.processIDMap.begin();

	std::cout << "Valid processes are: ";
	for (int i = 0; i < 6; i++) {
		std::cout << std::endl;
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
		it++;
	}
	std::cout << std::endl;
}
