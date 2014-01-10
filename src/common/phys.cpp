#include "game.hpp"

//======================================================================


fired::Phys::Phys() {
	jumpdown      = false;
	jumpdownLevel = 0;
}

//======================================================================


void fired::Phys::calculate() {
	rect   = sf::FloatRect(pos, size);
	center = pos + size / 2.0f;
}
