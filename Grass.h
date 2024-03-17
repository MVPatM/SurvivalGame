#pragma once
#include "Critter.h"

class Grass : public Critter {
public:
	Grass() : Critter() {};
	Grass(const Coordinator& p);
	bool move(const char w[][sz]) {}
	bool starve() {}
	bool breed() {}
};