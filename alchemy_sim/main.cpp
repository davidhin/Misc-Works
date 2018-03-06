#include "src/ingredient.h"
#include "src/plant.h"
#include "src/mineral.h"
#include "src/other.h"
#include "src/mix.h"
#include <iostream>
#include <string>

typedef std::unordered_map<std::string, ingredient*> ingredientMap;

int main() {
	// Generate library of ingredients
	ingredientMap* myIngredients = new ingredientMap;
	mix::ingredientLibrary(myIngredients);
	
	ingredient** base = new ingredient*;
	ingredient** middle = new ingredient*;
	ingredient** top = new ingredient*;

	std::cout << "Welcome to the alchemy simulator! ";
	mix::addIngredient(myIngredients, base, "first");
	mix::addIngredient(myIngredients, middle, "second");
	mix::addIngredient(myIngredients, top, "third");

	ingredient** totalIngredients[3] = { base, middle, top };
	mix::finalCalculations(totalIngredients);

	delete base, middle, top;
	myIngredients->clear();
}

/*
Test inputs			Expected outputs
Invalid ingredient name		Appropriate output error message, allow another input
'show' when prompted		Show a table of the ingredients and properties
Valid ingredient name		Pass the selected ingredient pointer to "process" function
Invalid process			Appropriate output error message, allow another input
Valid process but not allowed	Appropriate output error message, return function
Valid process			Perform corresponding member function on the object 
*/
