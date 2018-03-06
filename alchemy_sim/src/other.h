#pragma once
#include "ingredient.h"

class other : public ingredient {
public:
	other() = delete;
	other(std::string nameIn);
	ingredient* clone() const { return new other(*this); }

private:
	void boil();
	void dry();
	void grind();
	void distil();
	void crystallise();
	void melt();
};
