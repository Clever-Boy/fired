#include "game.hpp"


//======================================================================


fired::MapItem::MapItem(unsigned int _count, const char *_name) {
	count = _count;
	strncpy(name, _name, sizeof(name));
}
