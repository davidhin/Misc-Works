#include "ingredient.h"
#include "mix.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <iomanip>

extern int roundUp(int numToRound, int multiple);

// ------------ Constructors ------------ //
ingredient::ingredient(std::string nameIn)
{
	name = nameIn;

	typedef void(ingredient::*ingProcess)();
	processes[0] = &ingredient::boil;
	processes[1] = &ingredient::dry;
	processes[2] = &ingredient::grind;
	processes[3] = &ingredient::distil;
	processes[4] = &ingredient::crystallise;
	processes[5] = &ingredient::melt;

	std::string processNames[6] = { "boil", "dry", "grind", "distil", "crystallise", "melt" };

	for (int i = 0; i < 6; i++) {
		// Create a map which maps an int to the process name
		processIDMap.insert({i,processNames[i] });
		// Create a map which maps a process name to the member function
		processMap.insert({ processNames[i], processes[i] });
	}

	for (int i = 0; i < 4; i++) {
		stats[i] = 0;
		elemModifiers[i] = 0;
	}

}

// Clone constructor
ingredient::ingredient(ingredient* i) 
{
	cost = i->getCost();
	reactionTime = i->getTime();
	for (int j = 0; j < 4; j++) {
		stats[j] = i->getStat(j);
		elemModifiers[j] = i->getElem(j);
	}
	ingType = i->getIngType();
	status = i->getStatus();
	name = i->getName();
}


// ------------  Getter functions ------------ //
std::string ingredient::getName() { return name; }
int ingredient::getCost() { return cost; }
std::string ingredient::getStatus() { return status; }
int ingredient::getStat(int statid) { return stats[statid]; }
int ingredient::getElem(int statid) { return elemModifiers[statid]; }
std::string ingredient::getIngType() { return ingType; }
int ingredient::getTime() { return reactionTime; }

// Print the ingredient and properties in tabular form
void ingredient::printIngredient() 
{
	mix::printColNames();
	std::cout
		<< std::setw(10) << ingType << std::setw(12) << name << "$" << std::setw(6) << cost;
	for (int i = 0; i < 4; i++)
		std::cout << (getStat(i) >= 0 ? "+" : "-") << std::setw(6) << abs(getStat(i));
	for (int i = 0; i < 4; i++)
		std::cout << (getElem(i) >= 0 ? "+" : "-") << std::setw(7) << abs(getElem(i));
	std::cout << (getTime() > 0 ? "+" : "") << getTime() << std::setw(6) << "s";
	std::cout << std::endl;
}

// ------------  Perform process  ------------ //
void ingredient::doProcess()
{
	
	typedef void(ingredient::*ingProcess)();
	ingProcess process;
	// Get a string input from user and check if it is a valid process. If so, perform the
	// process, else exit the function.
	std::string input;
	std::cout << "Enter the process you want to perform. Type 'skip' to skip this step." << std::endl;
	std::cin >> input;

	if (input == "skip")
		return;

	std::unordered_map<std::string, ingProcess>::const_iterator got = processMap.find(input);

	while (got == processMap.end()){
		std::cout << "Invalid process. Pick another." << std::endl;
		std::cin >> input;

		if (input == "skip")
			return;

		got = processMap.find(input);
	}
	
	process = got->second;
	(this->*process)(); // Need clarification on why this works
}


void ingredient::showProcesses()
{
	std::unordered_map<int, std::string>::iterator it = processIDMap.begin();

	std::cout << "Valid processes are: ";
	for (int i = 0; i < 6; i++) {
		if (enabledProcesses[i]) {
			it = processIDMap.find(i);
			std::cout << it->second << " ";	
		}
	}
	std::cout << std::endl;
	return;
}

// ------------ Total Score ------------- //
void ingredient::calcCostTime() 
{
	// Calculate absolute sum of all stats
	totalStats = 0;
	for (int i = 0; i < 4; i++) {
		totalStats += stats[i];
		totalStats += elemModifiers[i];
	}

	// Random num btwn 1 and 2. Can change the reaction time / cost relationship to spice things up
	int timeCostRatio = rand() % 4 + 1;
	// Set cost and reaction time proportional to the amount of stat that the ingredient modifies
	if (rand() % 2 == 0) {
		cost = (totalStats / 10) * timeCostRatio;
		reactionTime = roundUp(totalStats / (5 * timeCostRatio), 10);
	}
	else {
		cost = (totalStats / 10) / timeCostRatio;
		reactionTime = roundUp((totalStats * timeCostRatio) / 5, 10);
	}
}


