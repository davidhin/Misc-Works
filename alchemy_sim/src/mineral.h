#pragma once
#include "ingredient.h"

class mineral : public ingredient {
public:
	mineral() = delete;
	mineral(std::string nameIn);

	ingredient* clone() const { return new mineral(*this); }
	
private:
	void boil();
	void dry();
	void grind();
	void distil();
	void crystallise();
	void melt();
};
