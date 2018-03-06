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
	ingredientMap* myIngredients = new ingredientMap;
	mix::ingredientLibrary(myIngredients);

	std::string input;
	std::cin >> input;

	ingredientMap::const_iterator got = myIngredients->find(input);

	while (got == myIngredients->end()) {
		if (input == "show") {
			mix::displayIngredients(myIngredients);
			std::cin >> input;
		}
		else {
			std::cout << "Invalid ingredient. Type 'show' to show the list of available ingredients." << std::endl;
			std::cin >> input;
		}
		got = myIngredients->find(input);
	}

	std::cout << got->second->getName() << std::endl;
}
