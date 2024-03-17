#include "Tiger.h"
#include <iostream>

// program이 도는 시간이 너무 빨라서 time의 값에 변화가 없다. 그래서 seed값이 항상 같으므로 rand를 통해서 나오는 값이 항상 일정하다.
bool Tiger::move(const char w[][sz]) {
	int dir_index = rand();
	int py = GetCritterYpos();
	int px = GetCritterXpos();
	int vx, vy;

	// for문의 3번째 위치에 있는 연산은 마지막 반복이 끝나더라도 진행을 하므로 착각을 하면 안된다.
	for (int i = 0; i < dir_num; i++) {
		++dir_index %= dir_num;
		vx = GetVarX(dir_index);
		vy = GetVarY(dir_index);
	
		if (!checkOutOfBound(py + vy, px + vx) && w[py + vy][px + vx] == 'R')
			break;
	}

	if (w[py + vy][px + vx] == 'T' || w[py + vy][px + vx] == 'H')
		return false;

	if (checkOutOfBound(py + vy, px + vx))
		return false;

	AddPosX(dir_index);
	AddPosY(dir_index);
	return true;
}

bool Tiger::starve() {
	DecreaseHp();

	if (isEatRabbit) {
		SetHp(3);
		isEatRabbit = true;
	}

	return !GetHp();
}

bool Tiger::breed() {
	DecreaseBreed();
	if (!BreedTime) {
		BreedTime = 4;
		return true;
	}

	return false;
}
