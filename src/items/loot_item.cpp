#include "game.hpp"


//======================================================================


fired::LootItem::LootItem(fired::BaseItem *_base, unsigned int _minCount, unsigned int _maxCount, float _probability) {
	base        = _base;
	minCount    = _minCount;
	maxCount    = _maxCount;
	probability = _probability;
}
