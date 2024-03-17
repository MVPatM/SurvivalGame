/*
1.rand함수는 임의의 수를 return을 해주는 함수이다.
프로그램이 만들어지면 rand를 통해서 나오는 값이 일정하다.
0부터 rand_max(32767)까지의 값중 임의의 값을 return한다. 
2. srand함수는 seed값을 넣어서 rand함수에 나오는 값을 초기화 시켜준다.
    프로그램이 실행 될때마다 rand함수를 초기화 시키면 되기 때문에 프로그램당 한번만 사용을 하면 된다.
   그런데 seed값이 일정하면 rand에서 나오는 값이 일정하다.
3. time함수는 1970년 1월 1일부터 경과된 시간을 sec을 통해서 return을 하는 함수이다.
*/
/*
code를 수정을 하였으면 왜 수정을 하였는 지를 주석을 이용해서 적어놓자
그렇지 않으면 까먹어서 다른 안 좋은 방향으로 code를 수정하게 된다.
*/

// hp문제 해결해야함 
// rabbit쪽 문제 해결을 해야함
#include "CritterHandler.h"

CritterHandler::CritterHandler() {
	int itr, py, px, num;
	bool iserror;
	string line;
	tigers = new Tiger* [CrtLimit];
	rabbits = new Rabbit * [CrtLimit];
	grasses = new Critter * [CrtLimit];
	pits = new Critter * [CrtLimit];
	hunter = new Hunter(Coordinator(rand() % sz, rand() % sz));

	for (int i = 0; i < CrtLimit; i++) {
		tigers[i] = nullptr;
		rabbits[i] = nullptr;
		grasses[i] = nullptr;
		pits[i] = nullptr;
	}
	memset(world, '-', sizeof(world));
	std::fill(&idx[0][0], &idx[sz - 1][sz], -1);
	world[hunter->GetCritterYpos()][hunter->GetCritterXpos()] = 'H';

	// Input the number
	do {
		iserror = false;

		while (1) {
			cout << "Enter initial number of rabbits: ";
			cin >> line;
			stringstream ss(line);
			ss >> num;
			if (ss.eof()) {
				rabbit_num = num;
				break;
			}
		}
		
		while (1) {
			cout << "Enter initial number of tigers: ";
			cin >> line;
			stringstream ss(line);
			ss >> num;
			if (ss.eof()) {
				tiger_num = num;
				break;
			}
		}
		while (1) {
			cout << "Enter initial number of grasses: ";
			cin >> line;
			stringstream ss(line);
			ss >> num;
			if (ss.eof()) {
				grass_num = num;
				break;
			}
		}
		while (1) {
			cout << "Enter initial number of pits: ";
			cin >> line;
			stringstream ss(line);
			ss >> num;
			if (ss.eof()) {
				pit_num = num;
				break;
			}
		}

		while (1) {
			cout << "Enter initial number of potions: ";
			cin >> line;
			stringstream ss(line);
			ss >> num;
			if (ss.eof()) {
				hunter->SetPotion(num);
				break;
			}
		}

		// 전체 critter의 합이 100이 넘는지를 check하는 code이다.
		if (tiger_num + rabbit_num + grass_num + pit_num >= 100)
			iserror = true;
	} while (iserror);

	itr = rabbit_num;
	while (itr) {
		py = rand() % sz;
		px = rand() % sz;
		if (world[py][px] != '-')
			continue;

		rabbits[itr - 1] = new Rabbit(Coordinator(py, px));
		world[py][px] = 'R';
		idx[py][px] = --itr;
	}

	itr = tiger_num;
	while (itr) {
		py = rand() % sz;
		px = rand() % sz;
		if (world[py][px] != '-')
			continue;

		tigers[itr - 1] = new Tiger(Coordinator(py, px));
		world[py][px] = 'T';
		idx[py][px] = --itr;
	}

	itr = grass_num;
	while (itr) {
		py = rand() % sz;
		px = rand() % sz;
		if (world[py][px] != '-')
			continue;

		grasses[itr - 1] = new Critter(Coordinator(py, px), 0);
		world[py][px] = '*';
		idx[py][px] = --itr;
	}

	itr = pit_num;
	while (itr) {
		py = rand() % sz;
		px = rand() % sz;
		if (world[py][px] != '-')
			continue;

		pits[itr - 1] = new Critter(Coordinator(py, px), 0);
		world[py][px] = 'O';
		idx[py][px] = --itr;
	}

	born_rabbit = rabbit_num;
	starved_rabbit = 0;
	captured_rabbit = 0;
	fallen_rabbit = 0;
	born_tiger = tiger_num;
	starved_tiger = 0;
	captured_tiger = 0;
	fallen_tiger = 0;
	TimeStep = 0;
	disappeared_grass = 0;
	isGameOver = false;
	now_grass_num = grass_num;
}

CritterHandler::~CritterHandler() {
	for (int i = 0; i < CrtLimit; i++) {
		delete rabbits[i];
		delete tigers[i];
		delete grasses[i];
		delete pits[i];
		rabbits[i] = NULL;
		tigers[i] = NULL;
		grasses[i] = NULL;
		pits[i] = NULL;
	}

	delete[] rabbits;
	delete[] tigers;
	delete[] grasses;
	delete[] pits;
	delete hunter;
	rabbits = NULL;
	tigers = NULL;
	grasses = NULL;
	pits = NULL;
	hunter = NULL;
}

void CritterHandler::ShowTopInfo() const {
	cout << "Time step: " << TimeStep << "\n";
	cout << "<Score:" << hunter->GetScore() << ", Hp:" << hunter->GetHp() << ", Potions:" << hunter->GetPotion() << ">\n";
	cout << "\n";
}

void CritterHandler::ShowWorld() const {
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) 
			cout << world[i][j] << " ";
		cout << "\n";
	}
}

void CritterHandler::ShowBottomInfo() const {
	cout << std::left;
	cout << setw(20) << "number of rabbits: " << setw(10) << rabbit_num;
	cout << "    <born:" << born_rabbit <<", starve:" << starved_rabbit <<", captured:" << captured_rabbit <<", fall:" << fallen_rabbit <<">\n";
	cout << setw(20) << "number of tigers: " << setw(10) << tiger_num;
	cout << "    <born:" << born_tiger << ", starve:" << starved_tiger << ", captured:" << captured_tiger <<", fall:" << fallen_tiger << ">\n";
	cout << setw(20) << "number of grasses: " << setw(10) << grass_num << "\n";
	cout << setw(20) << "number of pits:  " << setw(10) << pit_num << "\n";
}

void CritterHandler::FinalMsg() const {
	cout << "Your Final Score is " << hunter->GetScore() << "\n";
	cout << "End of the Program";
}

int CritterHandler::GetBreedPos(const Coordinator& p) const {
	int dir_index = rand();
	int py = p.GetYpos();
	int px = p.GetXpos();

	for (int i = 0; i < dir_num; i++) {
		++dir_index %= dir_num;
		if (!isOutOfBound(py + dirY[dir_index], px + dirX[dir_index]) && world[py + dirY[dir_index]][px + dirX[dir_index]] == '-' )
			return dir_index;
	}

	return -1;
}

void CritterHandler::DeleteRabbit(int arrayi) {
	if (arrayi == rabbit_num - 1) {
		delete rabbits[arrayi];
		rabbits[arrayi] = nullptr;
		rabbit_num--;
		return;
	}
	
	delete rabbits[arrayi];
	rabbits[arrayi] = rabbits[--rabbit_num];
	rabbits[rabbit_num] = nullptr;
	if (rabbits[arrayi] != nullptr)
		idx[rabbits[arrayi]->GetCritterYpos()][rabbits[arrayi]->GetCritterXpos()] = arrayi;
}

// arrayi가 삭제되어 지는 index를 의미한다.
void CritterHandler::DeleteTiger(int arrayi) {
	if (arrayi == tiger_num - 1) {
		delete tigers[arrayi];
		tigers[arrayi] = nullptr;
		tiger_num--;
		return;
	}

	delete tigers[arrayi];
	tigers[arrayi] = tigers[--tiger_num];
	tigers[tiger_num] = nullptr;
	if (tigers[arrayi] != nullptr) // if 문을 사용하지 않으면 c6011 warning이 발동이 되어질 수 있다.
		idx[tigers[arrayi]->GetCritterYpos()][tigers[arrayi]->GetCritterXpos()] = arrayi; // 발동 조건은 만약 heap메모리 할당에 실패할 ㅅ;
}

void CritterHandler::DeleteGrass(int arrayi) {
	if (arrayi == now_grass_num - 1) {
		delete grasses[arrayi];
		grasses[arrayi] = nullptr;
		now_grass_num--;
		return;
	}
	
	delete grasses[arrayi];
	grasses[arrayi] = grasses[--now_grass_num];
	grasses[now_grass_num] = nullptr;
	if (grasses[arrayi] != nullptr)
		idx[grasses[arrayi]->GetCritterYpos()][grasses[arrayi]->GetCritterXpos()] = arrayi;
}

void CritterHandler::HunterAction() {
	Coordinator before_pos = hunter->GetCritterPos();
	if (!hunter->move(world))
		return;

	Coordinator hunter_pos = hunter->GetCritterPos();
	int hy = hunter_pos.GetYpos();
	int hx = hunter_pos.GetXpos();
	char crtKind = world[hy][hx];
	int crtidx = idx[hy][hx];
	// move를 통해 얻어지는 결과 계산a
	if (crtKind == 'T') {
		DeleteTiger(crtidx);
		hunter->EatTiger();
		captured_tiger++;
	}
	else if (crtKind == 'R') {
		DeleteRabbit(crtidx);
		hunter->EatRabbit();
		captured_rabbit++;
	}
	else if (crtKind == '*') {
		DeleteGrass(crtidx);
		disappeared_grass++;
	}
	else if (crtKind == 'O') {
		isGameOver = true;
		return;
	}

	world[before_pos.GetYpos()][before_pos.GetXpos()] = '-';
	idx[hy][hx] = -1;
	world[hy][hx] = 'H';
	isGameOver = hunter->starve();
}

void CritterHandler::TigerAction() {
	Coordinator before_pos, tiger_pos;
	int crtidx, itr_num;
	char crtkind;

	itr_num = tiger_num;
	for (int i = 0; i < itr_num; i++) {
		before_pos = tigers[i]->GetCritterPos();
		tiger_pos = tigers[i]->GetCritterPos();

		if (tigers[i]->move(world)) {
			tiger_pos = tigers[i]->GetCritterPos();
			crtkind = world[tiger_pos.GetYpos()][tiger_pos.GetXpos()];
			crtidx = idx[tiger_pos.GetYpos()][tiger_pos.GetXpos()]; // tiger가 움직일 위치에 있는 object의 array index이다.
			world[before_pos.GetYpos()][before_pos.GetXpos()] = '-';

			// hunter한테는 갈 경우가 발생하지 않는다. empty로 가면 아무일도 발생 하지 않는다.
			if (crtkind == 'R') {
				DeleteRabbit(crtidx);
				tigers[i]->EatRabbit();
				captured_rabbit++;
			}
			else if (crtkind == '*') {
				DeleteGrass(crtidx);
				disappeared_grass++;
			}
			else if (crtkind == 'O') {
				DeleteTiger(i--);
				fallen_tiger++;
				itr_num--;
				continue;
			}
			idx[tiger_pos.GetYpos()][tiger_pos.GetXpos()] = i;
			world[tiger_pos.GetYpos()][tiger_pos.GetXpos()] = 'T';
		}
		//starve
		if (tigers[i]->starve()) {
			DeleteTiger(i--);
			starved_tiger++;
			world[tiger_pos.GetYpos()][tiger_pos.GetXpos()] = '-';
			itr_num--;
			continue;
		}
		//breed
		if (tigers[i]->breed()) {
			int breedpos = GetBreedPos(tiger_pos);
			if (breedpos != -1) {
				int born_y = tiger_pos.GetYpos() + dirY[breedpos];
				int born_x = tiger_pos.GetXpos() + dirX[breedpos];
				tigers[tiger_num] = new Tiger(Coordinator(born_y, born_x));
				world[born_y][born_x] = 'T';
				idx[born_y][born_x] = tiger_num++;
				born_tiger++;
			}
		}
	}
}

void CritterHandler::RabbitAction() {
	Coordinator before_pos, rabbit_pos;
	int ry, rx, crtidx, itr_num;
	char crtkind;
	itr_num = rabbit_num;
	// nullptr로 하면 새로 생긴 critter에 대해서도 move등을 하기 때문에 문제가 발생한다.
	for (int i = 0; i < itr_num; i++) {
		before_pos = rabbits[i]->GetCritterPos();
		rabbit_pos = rabbits[i]->GetCritterPos();

		if (rabbits[i]->move(world)) {
			rabbit_pos = rabbits[i]->GetCritterPos();
			ry = rabbit_pos.GetYpos();
			rx = rabbit_pos.GetXpos();
			crtkind = world[ry][rx];
			crtidx = idx[ry][rx];
			world[before_pos.GetYpos()][before_pos.GetXpos()] = '-';

			if (crtkind == '*') {
				DeleteGrass(crtidx);
				rabbits[i]->EatGrass();
				disappeared_grass++;
			}
			else if (crtkind == 'O') { // pits에 빠지면 그 자리에 작동하지 않았던 rabbit이 오는데 이것을 move시키지 않는다.
				DeleteRabbit(i--);
				fallen_rabbit++;
				itr_num--;
				continue;
			}
			
			idx[ry][rx] = i;
			world[ry][rx] = 'R';
		}

		if (rabbits[i]->starve()) {
			DeleteRabbit(i--);
			starved_rabbit++;
			itr_num--;
			world[rabbit_pos.GetYpos()][rabbit_pos.GetXpos()] = '-';
			continue;
		}

		if (rabbits[i]->breed()) {
			int breedpos = GetBreedPos(rabbit_pos);
			if (breedpos != -1) {
				int born_y = rabbit_pos.GetYpos() + dirY[breedpos];
				int born_x = rabbit_pos.GetXpos() + dirX[breedpos];
				rabbits[rabbit_num] = new Rabbit(Coordinator(born_y, born_x));
				world[born_y][born_x] = 'R';
				idx[born_y][born_x] = rabbit_num++;
				born_rabbit++;
			}
		}
	}
}

void CritterHandler::GrassAction() {
	int py, px;

	for (int i = disappeared_grass; i > 0; i--) {
		while (1) {
			py = rand() % sz;
			px = rand() % sz;
			if (world[py][px] == '-') {
				grasses[now_grass_num] = new Critter(Coordinator(py, px), 0);
				world[py][px] = '*';
				idx[py][px] = now_grass_num++;
				break;
			}
		}
	}
}

void CritterHandler::InitSetting() {
	born_rabbit = 0;
	starved_rabbit = 0;
	fallen_rabbit = 0;
	captured_rabbit = 0;
	born_tiger = 0;
	starved_tiger = 0;
	fallen_tiger = 0;
	captured_tiger = 0;
	disappeared_grass = 0;
	TimeStep++;
	now_grass_num = grass_num;
}