#include "game.hpp"


//======================================================================


fired::BaseMapObject::BaseMapObject(const char *_name, sf::Vector2f _pos, fired::MapObjectType _type) {
	type = _type;
	pos  = _pos;

	strncpy(decorName, _name, sizeof(decorName));
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
