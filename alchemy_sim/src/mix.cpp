#include "ingredient.h"
#include "plant.h"
#include "mineral.h"
#include "mix.h"
#include "other.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <assert.h>

// Rounding
int roundUp(int numToRound, int multiple) 
{
	assert(multiple);
	return ((numToRound + multiple - 1) / multiple) * multiple;
}

// A hashmap with a string key and pointer to an ingredient object as value
typedef std::unordered_map<std::string, ingredient*> ingredientMap;

// load ingredient library
void mix::ingredientLibrary(ingredientMap* map) 
{
	std::string plantNames[5] = { "tulip", "root", "orchid", "apple", "grapeseed" };
	std::string mineralNames[5] = { "platinum", "iron", "zinc", "palladium", "manganese" };
	std::string otherNames[5] = { "claws", "bones", "heart", "ashes", "feathers" };
	for (int i = 0; i < 5; i++) {
		map->insert({ plantNames[i], new plant(plantNames[i]) });
		map->insert({ mineralNames[i], new mineral(mineralNames[i]) });
		map->insert({ otherNames[i], new other(otherNames[i]) });
	}
}

// Print column names for a table (used with next function) 
void mix::printColNames() 
{
	std::string statNames[4] = { "HP", "Atk", "Def", "Spd" };
	std::string resistNames[4] = { "Fire", "Water", "Earth", "Wind" };
	std::cout << std::endl << std::left << std::setw(10) << "Type" << std::setw(12) << "Name" << std::setw(7) << "Cost";
	for (int i = 0; i < 4; i++)
		std::cout << std::setw(7) << statNames[i];
	for (int i = 0; i < 4; i++)
		std::cout << std::setw(8) << resistNames[i];
	std::cout << "ReactTime";
	std::cout << std::endl;
}

// display all ingredients and properties in table. If specificIngredient parameter is unassigned, display all. Else, display that ingredient. 
void mix::displayIngredients(ingredientMap* map) 
{
	// Set starting point for map iteration
	ingredientMap::iterator it = map->begin();

	mix::printColNames();

	// Display ingredient properties
	while (it != map->end()) {
		std::cout
			<< std::setw(10)
			<< it->second->getIngType()
			<< std::setw(12)
			<< it->second->getName()
			<< "$" << std::setw(6)
			<< it->second->getCost();
			for (int i = 0; i < 4; i++)
				std::cout << (it->second->getStat(i) >= 0 ? "+" : "-") << std::setw(6) << abs(it->second->getStat(i));
			for (int i = 0; i < 4; i++)
				std::cout << (it->second->getElem(i) >= 0 ? "+" : "-") << std::setw(7) << abs(it->second->getElem(i));
			std::cout << (it->second->getTime() > 0 ? "+" : "") << it->second->getTime() << std::setw(6) << "s" << std::endl;
		it++;
	}
	std::cout << std::endl;
}

// Perform a process on ingredient if user selects yes
void mix::processIngredient(ingredient* currentIngredient) 
{
	std::cout << "What would you like to do to the ingredient? ";
	currentIngredient->showProcesses(); 
	currentIngredient->doProcess();
}

// User selects an ingredient
void mix::pickIngredient(ingredientMap* map, ingredient** currentIngredient) 
{
	std::string input;
	std::cin >> input;
	ingredientMap::const_iterator got = map->find(input);
	while (got == map->end()) {
		if (input == "show") {
			displayIngredients(map);
			std::cin >> input;
		}
		else {
			std::cout << "Invalid ingredient. Type 'show' to show the list of available ingredients." << std::endl;
			std::cin >> input;
		}
		got = map->find(input);
	}
	
	// Clone the ingredient before executing processIngredient function
	*currentIngredient = got->second->clone();
	mix::processIngredient(*currentIngredient);
}

// Add an ingredient to the cauldron
void mix::addIngredient(ingredientMap* map, ingredient** ingredientIn, std::string ingType) 
{
	std::cout << "Please type in the name of your " << ingType << " " << "ingredient" << "." << std::endl;
	std::cout << "Type 'show' to show the list of available ingredients." << std::endl;
	mix::pickIngredient(map, ingredientIn);
	std::cout << "You added a " << (*ingredientIn)->getName() << " to the cauldron. " << std::endl << std::endl;
	std::cout << "------------------------- " << std::endl << std::endl;
}

// Final Calculations
// Return the position of the maximum value of an array of integers
int maxPos(int* arr, int n) 
{
	int max = -2147483648;
	int pos = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
			pos = i;
		}
	}
	return pos;
}

// Descriptive word for strength
std::string strDes(int num) 
{
	int numAbs = abs(num);
	if (0 <= numAbs && numAbs <= 50) return "Pathetic";
	if (50 < numAbs && numAbs <= 150) return "Weak";
	if (150 < numAbs && numAbs <= 400) return "Moderate";
	if (400 < numAbs && numAbs <= 700) return "Strong";
	if (700 < numAbs && numAbs <= 999) return "Extreme";
	if (numAbs >= 1000) return "Ultimate";
}

// Show final stats of potion
void mix::finalCalculations(ingredient** finalList[3]) 
{
	std::string statNames[4] = { "Healing", "Attack", "Defense", "Speed" };
	std::string resistNames[4] = { "Fire", "Water", "Earth", "Wind" };

	int costFinal = 0;
	int statsFinal[4] = { 0,0,0,0 };
	int elemsFinal[4] = { 0,0,0,0 };
	int timeFinal = 0;
	for (int i = 0; i < 3; i++) {
		costFinal += (*(finalList[i]))->getCost();
		timeFinal += (*(finalList[i]))->getTime();
		for (int j = 0; j < 4; j++) {
			statsFinal[j] += (*(finalList[i]))->getStat(j);
			elemsFinal[j] += (*(finalList[i]))->getElem(j);
		}
	}

	int maxStat = maxPos(statsFinal, 4);
	int maxElem = maxPos(elemsFinal, 4);

	std::cout << "Total Cost: $" << costFinal << std::endl;
	std::cout << "Total HP: " << (statsFinal[0] >= 0 ? "+" : "-") << abs(statsFinal[0]) << std::endl;
	std::cout << "Total Atk: " << (statsFinal[1] >= 0 ? "+" : "-") << abs(statsFinal[1]) << std::endl;
	std::cout << "Total Def: " << (statsFinal[2] >= 0 ? "+" : "-") << abs(statsFinal[2]) << std::endl;
	std::cout << "Total Spd: " << (statsFinal[3] >= 0 ? "+" : "-") << abs(statsFinal[3]) << std::endl;
	std::cout << "Total Fire: " << (elemsFinal[0] >= 0 ? "+" : "-") << abs(elemsFinal[0]) << std::endl;
	std::cout << "Total Water: " << (elemsFinal[1] >= 0 ? "+" : "-") << abs(elemsFinal[1]) << std::endl;
	std::cout << "Total Earth: " << (elemsFinal[2] >= 0 ? "+" : "-") << abs(elemsFinal[2]) << std::endl;
	std::cout << "Total Wind: " << (elemsFinal[3] >= 0 ? "+" : "-") << abs(elemsFinal[3]) << std::endl;

	std::cout << "Final Potion: " << std::endl;
	std::cout << "Name: "
		<< (statsFinal[0] > 100 ? "Rejuvenating " : "")
		<< (statsFinal[0] < -100 ? "Painful " : "")
		<< "potion of "
		<< strDes(statsFinal[maxStat]) << " "
		<< statNames[maxStat]
		<< " with "
		<< strDes(elemsFinal[maxElem])
		<< " "
		<< resistNames[maxElem]
		<< " resistance."
		<< std::endl;

	if (timeFinal < 0) { timeFinal = 0; }
	std::cout << "Total reaction time: " << timeFinal << "s" << std::endl;
}


/*
// display all ingredients and properties of an ingredientMap object, in table format
extern void displayIngredients(ingredientMap* map);
// Perform a process on a given ingredient if user input is yes
extern void processIngredient(ingredient* currentIngredient);
// User selects an ingredient
extern void pickIngredient(ingredientMap* map, ingredient** currentIngredient);
// Print column names for a table of ingredients
extern void printColNames();
// Return the position of the maximum value of an array of integers
extern int maxPos(int* arr, int n);
// A function that takes an int number and returns a strength descriptive word
extern std::string strDes(int num);

// load ingredient library
extern void ingredientLibrary(ingredientMap* map);
// Add an ingredient to the ingredientMap, with an associated name ingtype (base, middle, top, first, second, etc).
extern void addIngredient(ingredientMap* map, ingredient** ingredientIn, std::string ingType);
// Print the final stats of potion and its name
extern void finalCalculations(ingredient** finalList[3]);

*/
