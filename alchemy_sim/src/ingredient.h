#pragma once
#include <string>
#include <unordered_map>

class ingredient 
{
protected:	
	// Inherent ingredient details
	std::string name;
	int cost, reactionTime, totalStats;
	std::string ingType;

	// Stats represented in array in order: HP, atk, def, spd 
	int stats[4];	

	// Elemental resists in order: fire, water, earth, wind
	int elemModifiers[4];

	// Calculate cost and reaction time based on attributes
	void calcCostTime();

	// All potential processes
	virtual void boil() = 0;
	virtual void dry() = 0;
	virtual void grind() = 0;
	virtual void distil() = 0;
	virtual void crystallise() = 0;
	virtual void melt() = 0;
	std::string status;

public:
	ingredient() = delete;
	ingredient(std::string nameIn);
	ingredient(ingredient *i);
	// Clone ingredients so that the one in the map remains unchanged
	virtual ingredient* clone() const = 0; 
	// Print individual ingredient properties
	void printIngredient();

	std::string getName();
	int getCost();
	std::string getStatus();
	int getStat(int statid);
	int getElem(int statid);
	int getTime();
	std::string getIngType();
	bool enabledProcesses[6];

	// show all valid processes
	void showProcesses();
	// execute an input process
	void doProcess();

	// A void member function with no parameters of the class ingredient
	typedef void(ingredient::*ingProcess)();
	// ProcessMap will map string names to the corresponding process
	std::unordered_map<std::string, ingProcess> processMap;
	// Num process map: maps integers 0-5 to each of the processes
	std::unordered_map<int, std::string> processIDMap;	
	// Array of pointers to member functions (processes, e.g. melt, dry)
	ingProcess processes[6];

};
