#include "game.hpp"


//======================================================================


fired::BaseMapObjectCollector::BaseMapObjectCollector(const char *_name, sf::Vector2f _pos) {
	type = moCollector;
	pos  = _pos;

	strncpy(decorName, _name, sizeof(decorName));
}

//======================================================================


void fired::BaseMapObjectCollector::generateLoot() {
	addItem(1, "weapon.plasmagun");
	addItem(1, "armor.body.leather");
}

//======================================================================


void fired::BaseMapObjectCollector::addItem(unsigned int _count, const char *_name) {
	items.push_back(new fired::MapItem(_count, _name));
}

//======================================================================


fired::MapObjectCollector::MapObjectCollector(fired::Decor *_decor) {
	type = moCollector;
	decor = _decor;
}
