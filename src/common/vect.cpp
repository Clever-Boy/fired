#include "game.hpp"

//======================================================================


sf::Vector2f vNorm(sf::Vector2f v) {
	return v / vLen(v);
}

//======================================================================


sf::Vector2f vSetLen(sf::Vector2f v, float l) {
	return vNorm(v) * l;
}

//======================================================================


sf::Vector2f rectCenter(sf::FloatRect rect) {
	return sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2);
}

//======================================================================


float vLen(sf::Vector2f v) {
	return sqrt(sqr(v.x) + sqr(v.y));
}

