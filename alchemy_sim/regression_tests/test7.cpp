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
	
	ingredient* myPlant = new plant("flower");
	myPlant->printIngredient();

	ingredient* myPlantClone = myPlant->clone();
	myPlantClone->printIngredient();

	std::cout << "delete the first plant" << std::endl;
	
	delete myPlant;
	
	std::cout << "Cloned plant" << std::endl;
	myPlantClone->printIngredient();
}
