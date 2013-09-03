#include "game.hpp"


//======================================================================


fired::MapItem::MapItem(fired::ItemType _type, unsigned int _count, const char *_name) {
	count = _count;
	type  = _type;

	strncpy(name   , _name, sizeof(name));
}
