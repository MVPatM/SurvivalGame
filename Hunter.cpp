#include "Hunter.h"

bool Hunter::move(const char w[][sz]) {
	int dir_index;
	bool isbreak;
	string dir;

	do {
		cout << "Input the moving direction( Up: 'w', Down: 's', Left: 'a', Right: 'd': ";
		isbreak = true;
		cin >> dir;

		if (dir == "w")
			dir_index = 0;
		else if (dir == "s")
			dir_index = 1;
		else if (dir == "a")
			dir_index = 2;
		else if (dir == "d")
			dir_index = 3;
		else if (dir == "wa")
			dir_index = 4;
		else if (dir == "wd")
			dir_index = 5;
		else if (dir == "sa")
			dir_index = 6;
		else if (dir == "sd")
			dir_index = 7;
		else {
			isbreak = false;
			std::cout << '\n';
		}
	} while (!isbreak);

	if (checkOutOfBound(GetCritterYpos() + GetVarY(dir_index), GetCritterXpos() + GetVarX(dir_index)))
		return false;

	AddPosX(dir_index);
	AddPosY(dir_index);
	return true;
}

bool Hunter::starve() {
	string ans;
	DecreaseHp();
	if (potion > 0) {
		do {
			cout << "Are you going to use potion(Yes: 'y', No: 'n'): ";
			cin >> ans;

			if (ans == "y") {
				if (potion > 0) {
					SetHp(5);
					potion--;
				}
				break;
			}
			else if (ans == "n")
				break;
		} while (1);
	}

	if (isEatTIger) {
		SetHp(5);
		isEatTIger = false;
	}

	if (isEatRabbit) {
		SetHp(std::min(5, GetHp() + 2));
		isEatRabbit = false;
	}

	return !GetHp();
}