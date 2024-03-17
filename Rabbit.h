#pragma once
#include "Critter.h"

class Rabbit : public Critter {
private:
	int BreedTime;
	bool isEatgrass;
	inline void DecreaseBreed() { BreedTime--; }
public:
	Rabbit() :Critter(), BreedTime(0), isEatgrass(false) {}
	Rabbit(const Coordinator& p) :Critter(p, 3), BreedTime(3), isEatgrass(false) {}
	inline void EatGrass() { isEatgrass = true; }
	virtual bool move(const char w[][sz]);
	virtual bool starve();
	virtual bool breed();
};