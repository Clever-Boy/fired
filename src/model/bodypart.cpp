#include "game.hpp"

//======================================================================


fired::BaseBodypart::~BaseBodypart() {
	delete sprite;
	delete chunk;
	delete texture;
}
