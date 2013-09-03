#include "game.hpp"


//======================================================================


fired::LootItem::LootItem(fired::ItemType _type, const char *_name, unsigned int _minCount, unsigned int _maxCount, float _probability) {
	type        = _type;
	minCount    = _minCount;
	maxCount    = _maxCount;
	probability = _probability;

	strncpy(name, _name, sizeof(name));
}
