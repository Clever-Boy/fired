#ifndef __LOOT_ITEM
#define __LOOT_ITEM


namespace fired {
	struct LootItem {
		fired::ItemType type;
		char            name[64];

		unsigned int    minCount;
		unsigned int    maxCount;
		float           probability;


		LootItem(fired::ItemType _type, const char *_name, unsigned int _minCount, unsigned int _maxCount, float _probability);
	};
}

#endif
