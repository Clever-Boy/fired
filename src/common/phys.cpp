#include "phys.hpp"

//======================================================================


void fired::Phys::calculate() {
	rect   = sf::FloatRect(pos, size);
	head   = sf::FloatRect(pos, sf::Vector2f(size.x, size.y / 3));
	center = pos + size / 2.0f;
}
