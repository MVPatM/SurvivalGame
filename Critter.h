#pragma once
#include "Coordinator.h"
#include<cstdlib>
#include<ctime>
#include<cstring>
#define sz 10
#define dir_num 4

class Critter {
private:
	int dirY[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
	int dirX[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };
	Coordinator pos;
	int hp;
public:
	Critter() :hp(0) { SetPos(Coordinator()); }
	Critter(int y, int x, int h);
	Critter(const Coordinator& p, int h);
	~Critter() {}
	inline int GetCritterYpos() const { return pos.GetYpos(); }
	inline int GetCritterXpos() const { return pos.GetXpos(); }
	inline int GetVarY(int idx) { return dirY[idx]; }
	inline int GetVarX(int idx) { return dirX[idx]; }
	inline void AddPosY(int idx) { pos.MovY(dirY[idx]); }
	inline void AddPosX(int idx) { pos.MovX(dirX[idx]); }
	inline Coordinator GetCritterPos() const { return pos; }
	inline int GetHp() const { return hp; }
	inline void SetHp(int h) { hp = h; }
	inline void DecreaseHp() { hp--; }
	inline bool checkOutOfBound(int y, int x) const { return y < 0 || y > 9 || x < 0 || x > 9; }
	//inline bool OutOfBound(int idx) {return pos.GetYpos() + dirY[idx] }
	inline void SetPos(const Coordinator& p) { pos = p; }
	bool move(const char w[][sz]) { return false; } // when not moving, return false	
	bool starve() { return false; }
	bool breed() { return false; }
};