#include "game.hpp"


//======================================================================


fired::BaseMapObject::BaseMapObject(const char *_name, sf::Vector2f _pos, fired::MapObjectType _type) {
	type = _type;
	pos  = _pos;

	strncpy(decorName, _name, sizeof(decorName));
}

//======================================================================


fired::BaseMapObjectCollector::BaseMapObjectCollector(const char *_name, sf::Vector2f _pos, fired::MapObjectType _type) {
	type = _type;
	pos  = _pos;

	strncpy(decorName, _name, sizeof(decorName));
}

//======================================================================


void fired::BaseMapObjectCollector::generateLoot() {
	items.push_back(new fired::MapItem(itMoney, 20 + random() % 20, "credits"));

	if (random() % 100 > 50) items.push_back(new fired::MapItem(itWeapon, 1, "pistol"));
	if (random() % 100 > 30) items.push_back(new fired::MapItem(itWeapon, 1, "bar"));
	if (random() % 100 > 80) items.push_back(new fired::MapItem(itWeapon, 1, "rifle"));
}

//======================================================================


fired::MapObject::MapObject(fired::Decor *_decor) {
	type = moNone;
	decor = _decor;
}

//======================================================================


fired::MapObject::~MapObject() {
	if (decor) delete decor;
}

//======================================================================


void fired::MapObject::render() {
	if (decor) decor->render();
}

//======================================================================


fired::MapObjectCollector::MapObjectCollector(fired::Decor *_decor) {
	type = moCollector;
	decor = _decor;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			items[i][j] = NULL;
}

//======================================================================


fired::MapObjectCollector::~MapObjectCollector() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if(items[i][j]) delete items[i][j];
}
