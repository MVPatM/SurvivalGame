#pragma once
#include "Critter.h"
#include "Hunter.h"
#include "Tiger.h"
#include "Rabbit.h"
#include "Coordinator.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#define sz 10
#define CrtLimit 100
#define dir_num 4

using std::cout; 
using std::cin; 
using std::ios_base;
using std::string;
using std::stringstream;
using std::setw;

class CritterHandler {
private:
	int dirY[4] = { -1, 1, 0, 0};
	int dirX[4] = { 0, 0, -1, 1};
	char world[sz][sz]; // (y, x), 이전의 cell과 new cell 모두에게 관심을 가져야 한다. 
	int idx[sz][sz]; // 새로 생기는 cell에만 관심을 가지면 된다.
	Hunter* hunter;
	Tiger** tigers;
	Rabbit** rabbits;
	Critter** pits;
	Critter** grasses;
	int tiger_num, rabbit_num, pit_num, grass_num, now_grass_num;
	int born_rabbit, starved_rabbit, captured_rabbit, fallen_rabbit;
	int born_tiger, starved_tiger, captured_tiger, fallen_tiger;
	int disappeared_grass;
	int TimeStep;
	bool isGameOver;
	int GetBreedPos(const Coordinator& p) const;
	void DeleteTiger(int arrayi);
	void DeleteRabbit(int arrayi);
	void DeleteGrass(int arrayi);
	inline bool isOutOfBound(int y, int x) const { return y < 0 || y > 9 || x < 0 || x > 9; }
public:
	CritterHandler();
	~CritterHandler();
	void ShowTopInfo() const;
	void ShowWorld() const;
	void ShowBottomInfo() const;
	void FinalMsg() const;
	inline void ClearScreen() const { system("cls"); }
	inline bool GameOver() const { return isGameOver; }
	void HunterAction();
	void TigerAction();
	void RabbitAction();
	void GrassAction();
	void InitSetting();
};
