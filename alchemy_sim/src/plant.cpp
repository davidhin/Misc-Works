#include "ingredient.h"
#include "plant.h"
#include <iostream>
#include <string>
#include <random>

extern int roundUp(int numToRound, int multiple);

plant::plant(std::string nameIn)
: ingredient(nameIn)
{
	ingType = "Plant";
	// Enable certain processes to be performed on the ingredient
	int processArr[6] = { rand() % 2,1,1,1,0,0 };
	for (int i = 0; i < 6; i++)
		enabledProcesses[i] = processArr[i];

	// Set health modifying value and randomise it to be negative or positive
	stats[0] = roundUp(rand() % 200,20);
	if (rand() % 2 == 0)
		stats[0] *= -1;

	// Add a random number to either Defence, Water or Earth. Repeat 3 times. 
	for (int i = 0; i < 3; i++) {
		if (rand() % 2 == 0) 
			stats[2] += roundUp(rand() % 60 + 1, 10);
		else
			elemModifiers[rand() % 2 + 1] += roundUp(rand() % 60 + 20, 10);
	}

	// Boost stats if ingredient decreases HP
	if (stats[0] < 0) {
		for (int i = 2; i < 4; i++) {
			stats[i] *= -stats[0] / 20;
			elemModifiers[i] *= -stats[0] / 20;
		}
	}

	calcCostTime();
}

// ------------ Functions that are processes ------------ //
void plant::boil() 
{
	if (!enabledProcesses[0]) {
		std::cout << "Cannot boil " << name << "." << std::endl;
		return;
	}

	std::cout << "You boil the " << name << ". Cost increases. Water and wind increases." << std::endl;
	int change = rand() % 5 + 2;
	elemModifiers[2] += 60 * change;
	elemModifiers[3] += 40 * change;
	cost *= change;
	printIngredient();
}

void plant::dry()
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

void plant::grind()
{
	if (!enabledProcesses[2]) {
		std::cout << "Cannot grind " << name << "." << std::endl;
		return;
	}

	std::cout << "You grind the " << name << ". Cost increases. Reaction time decreases." << std::endl;
	int change = rand() % 4 + 2;
	cost *= change / 2;
	reactionTime /= change;
	printIngredient();
}

void plant::distil()
{
	if (!enabledProcesses[3]) {
		std::cout << "Cannot distil " << name << "." << std::endl;
		return;
	}

	std::cout << "You distil " << name << ". All attributes enchanced. Cost increases." << std::endl;
	for (int i = 0; i < 4; i++) {
		stats[i] *= 2;
		elemModifiers[i] *= 2;
	}

	cost *= 3;

	printIngredient();
}

void plant::crystallise()
{
	std::cout << "Cannot crystallise " << name << "." << std::endl;
}

void plant::melt()
{
	std::cout << "Cannot melt " << name << "." << std::endl;
}

