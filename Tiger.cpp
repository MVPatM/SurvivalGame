#include "Tiger.h"
#include <iostream>

// program�� ���� �ð��� �ʹ� ���� time�� ���� ��ȭ�� ����. �׷��� seed���� �׻� �����Ƿ� rand�� ���ؼ� ������ ���� �׻� �����ϴ�.
bool Tiger::move(const char w[][sz]) {
	int dir_index = rand();
	int py = GetCritterYpos();
	int px = GetCritterXpos();
	int vx, vy;

	// for���� 3��° ��ġ�� �ִ� ������ ������ �ݺ��� �������� ������ �ϹǷ� ������ �ϸ� �ȵȴ�.
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
