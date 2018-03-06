#pragma once
#include "ingredient.h"

class plant : public ingredient {
public:
	plant() = delete;
	plant(std::string nameIn);
	ingredient* clone() const { return new plant(*this); }

private:
	void boil();
	void dry();
	void grind();
	void distil();
	void crystallise();
	void melt();
};
