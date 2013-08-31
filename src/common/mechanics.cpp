#include "game.hpp"

//======================================================================


long levelXP(int level) {
	long res = 0;
	for (int i = 0; i < level; res += (i / 2 + 1) * 250, i++);
	return res;
}

//======================================================================


float armorReduction(unsigned int armor) {
	return 1.0f - 100.0f / (100.0f + (float)armor);
}
