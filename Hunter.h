#pragma once
#include "Critter.h"
#include <algorithm>
#include <iostream>

using std::string;
using std::cin;
using std::cout;

class Hunter:public Critter {
private:
	bool isEatRabbit, isEatTIger;
	int potion, score;
public:
	Hunter():Critter(), potion(0), score(0), isEatRabbit(false), isEatTIger(false) {}
	Hunter(const Coordinator& p) : Critter(p, 5), potion(0), score(0), isEatRabbit(false), isEatTIger(false) {}
	inline int GetScore() const { return score; }
	inline int GetPotion() const { return potion; }
	inline void SetPotion(int n) { potion = n; }
	inline void EatTiger() { isEatTIger = true, score += 2; }
	inline void EatRabbit() { isEatRabbit = true, score += 1; }
	virtual bool move(const char w[][sz]);
	virtual bool starve();
	virtual bool breed() { return false; }
};