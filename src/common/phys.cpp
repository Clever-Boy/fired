#include "game.hpp"

//======================================================================


fired::Phys::Phys() {
	jumpdown      = false;
	jumpdownLevel = 0;
}

//======================================================================


void fired::Phys::calculate() {
	rect   = sf::FloatRect(pos, size);
	head   = sf::FloatRect(pos + headOffset, headSize);
	center = pos + size / 2.0f;
}
