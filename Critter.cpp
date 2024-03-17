#include "Critter.h"

Critter::Critter(int y, int x, int h) {
	pos = Coordinator(y, x);
	hp = h;
}

Critter::Critter(const Coordinator& p, int h) {
	pos = p;
	hp = h;
}