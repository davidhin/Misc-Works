#include "ingredient.h"
#include "mineral.h"
#include <string>
#include <iostream>
#include <random>

extern int roundUp(int numToRound, int multiple);

mineral::mineral(std::string nameIn)
: ingredient(nameIn) 
{
	ingType = "Mineral";
	reactionTime = 0;

	//Enable certain processes to be performed on the ingredient
	bool i = rand() % 2;
	int processArr[6] = { 0,0,rand() & 2,0,i,!i };
	for (int i = 0; i < 6; i++)
		enabledProcesses[i] = processArr[i];

	for (int i = 0; i < 5; i++) {
		if (rand() % 4 == 0)
			elemModifiers[rand() % 5] += roundUp(rand() % 80 + 1, 10);
		else
			reactionTime -= roundUp(rand() % 80 + 1, 10);
	}

	// Calculate absolute sum of all stats
	totalStats = 0;
	for (int i = 0; i < 4; i++) {
		totalStats += abs(elemModifiers[i]);
		totalStats += abs(reactionTime);
	}

	cost = totalStats / 5;
}

// ------------ Functions that are processes ------------ //
void mineral::boil() 
{
	std::cout << "Cannot boil this type of ingredient" << std::endl;
}

void mineral::dry()
{
	std::cout << "Cannot dry " << name << "." << std::endl;
}

void mineral::grind()
{
	if (!enabledProcesses[2]) {
		std::cout << "Cannot grind " << name << "." << std::endl;
		return;
	}

	std::cout << "You grind the " << name << ". ";
	std::cout << "Reaction time is reduced, but cost increases.";
	if (reactionTime < 0)
		reactionTime *= 1.5;
	else
		reactionTime /= 2;
	cost *= 2;
	printIngredient();
}

void mineral::distil()
{
	std::cout << "Cannot distil " << name << "." << std::endl;
}

void mineral::crystallise()
{
	if (!enabledProcesses[4]) {
		std::cout << "Cannot crystallise " << name << "." << std::endl;
		return;
	}

	std::cout << "You crystallise the " << name << ". Defense and Earth increases, but cost and reaction time also increases." << std::endl;
	int increase = rand() % 150 + 100;
	stats[2] += roundUp(increase * 1.2, 5);
	elemModifiers[2] += roundUp(increase * 0.8,5);
	cost *= increase / 50;
	reactionTime /= increase / 50;
	printIngredient();

}

void mineral::melt()
{
	if (!enabledProcesses[5]) {
		std::cout << "Cannot melt " << name << "." << std::endl;
		return;
	}

	std::cout << "You melt the " << name << ". Cost, Attack, Fire increases. Reaction time and defence decreases." << std::endl;
	int change = rand() % 150 + 100;
	cost *= change / 70;
	stats[1] += roundUp(change * 1, 5);
	elemModifiers[0] += roundUp(change * 1.1, 5);
	stats[2] -= roundUp(change * 1.1, 5);
	reactionTime -= roundUp(change / 3, 10);
	printIngredient();
}
