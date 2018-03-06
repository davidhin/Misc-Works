#pragma once

#include "ingredient.h"
#include "plant.h"
#include "mineral.h"
#include "other.h"

typedef std::unordered_map<std::string, ingredient*> ingredientMap;

class mix {
public:
	static void ingredientLibrary(ingredientMap* map);
	static void printColNames();
	static void displayIngredients(ingredientMap* map);
	static void processIngredient(ingredient* currentIngredient);
	static void pickIngredient(ingredientMap* map, ingredient** currentIngredient);
	static void addIngredient(ingredientMap* map, ingredient** ingredientIn, std::string ingType);
	static void finalCalculations(ingredient** finalList[3]);
};
