#pragma once
#include "Critter.h"

class Tiger:public Critter {
private:
	int BreedTime;
	bool isEatRabbit;
	inline void DecreaseBreed() { BreedTime--; }
public:
	Tiger():Critter(), BreedTime(0), isEatRabbit(false) {}
	Tiger(const Coordinator& p) :Critter(p, 3), BreedTime(4), isEatRabbit(false) {}
	inline void EatRabbit() { isEatRabbit = true; }
	virtual bool move(const char w[][sz]);
	virtual bool starve();
	virtual bool breed();
};