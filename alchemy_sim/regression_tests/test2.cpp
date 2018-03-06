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
	mix::displayIngredients(myIngredients);

}
