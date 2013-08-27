#include "game.hpp"


//======================================================================


fired::MapObject::MapObject() {
	decor = NULL;
}

//======================================================================


void fired::MapObject::render() {
	if (decor) decor->render();
}

//======================================================================


fired::MapObjectCollector::MapObjectCollector() {
	return;
}

//======================================================================


fired::MapObjectCollector::~MapObjectCollector() {
	return;
}
