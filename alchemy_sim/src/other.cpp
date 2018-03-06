#include "ingredient.h"
#include "other.h"
#include <string>
#include <iostream>
#include <random>

extern int roundUp(int numToRound, int multiple);

other::other(std::string nameIn)
: ingredient(nameIn) 
{
	ingType = "Other";

	//Enable certain processes to be performed on the ingredient
	int processArr[6] = { 1,rand() % 2,1,rand() % 2,0,0 };
	for (int i = 0; i < 6; i++)
		enabledProcesses[i] = processArr[i];

	// Add a random number to any attribute except HP. Repeat 6 times. 
	for (int i = 0; i < 8; i++) {
		if (rand() % 2 == 0)
			stats[rand() % 5] += roundUp(rand() % 150 + 1, 10);
		else
			elemModifiers[rand() % 5] += roundUp(rand() % 150 + 1, 10);
	}

	calcCostTime();
}

// ------------ Functions that are processes ------------ //
void other::boil() 
{
	if (!enabledProcesses[0]) {
		std::cout << "Cannot boil " << name << "." << std::endl;
		return;
	}

	std::cout << "You boil the " << name << ". HP increases. Reaction time decreases. Cost increases." << std::endl;
	int change = rand() % 5 + 2;
	stats[0] += 60 * change;
	reactionTime -= 50;
	cost *= change;
	printIngredient();
}

void other::dry()
{
	if (!enabledProcesses[1]) {
		std::cout << "Cannot dry " << name << "." << std::endl;
		return;
	}

	std::cout << "You dry the " << name << ". Cost increases. Water decreases. Speed increases." << std::endl;
	int change = rand() % 5 + 2;
	stats[3] += 60 * change;
	elemModifiers[1] -= 40 * change;
	cost *= change * 0.8;
	printIngredient();
}

void other::grind()
{
	if (!enabledProcesses[2]) {
		std::cout << "Cannot grind " << name << "." << std::endl;
		return;
	}

	std::cout << "You grind the " << name << ". Cost increases. Speed increases. Reaction time decreases." << std::endl;
	int change = rand() % 4 + 2;
	cost *= change / 3;
	stats[3] += 50 * change;
	reactionTime /= change;
	printIngredient();
}

void other::distil()
{
	if (!enabledProcesses[3]) {
		std::cout << "Cannot distil " << name << "." << std::endl;
		return;
	}

	std::cout << "You distil " << name << ". All stats enchanced. Cost increases." << std::endl;
	for (int i = 0; i < 4; i++) {
		stats[i] *= 3;
	}
	cost *= 4;
	printIngredient();
}

void other::crystallise()
{
	std::cout << "Cannot crystallise " << name << "." << std::endl;
}

void other::melt()
{
	std::cout << "Cannot melt " << name << "." << std::endl;
}
