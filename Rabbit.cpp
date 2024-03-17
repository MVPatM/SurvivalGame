#include "Rabbit.h"

bool Rabbit::move(const char w[][sz]) {
	int dir_index = rand();
	int py = GetCritterYpos();
	int px = GetCritterXpos();
	int vx, vy;

	for (int i = 0; i < dir_num; i++) {
		++dir_index %= dir_num;
		vx = GetVarX(dir_index);
		vy = GetVarY(dir_index);

		if (!checkOutOfBound(py + vy, px + vx) && w[py + vy][px + vx] == '*')
			break;
	}

	if (w[py + vy][px + vx] == 'T' || w[py + vy][px + vx] == 'H' || w[py + vy][px + vx] == 'R')
		return false;
	if (checkOutOfBound(py + vy, px + vx))
		return false;

	AddPosX(dir_index);
	AddPosY(dir_index);
	return true;
}

bool Rabbit::starve() {
	DecreaseHp();
	if (isEatgrass) {
		SetHp(3);
		isEatgrass = false;
	}

	return !GetHp();
}

bool Rabbit::breed() {
	DecreaseBreed();
	if (!BreedTime) {
		BreedTime = 2;
		return true;
	}

	return false;
}