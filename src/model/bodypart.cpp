#include "game.hpp"

//======================================================================


void fired::BaseBodypart::deinit() {
	delete sprite;
	delete chunk;
	delete texture;
}