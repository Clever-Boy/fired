#ifndef __MAP_ITEM
#define __MAP_ITEM


namespace fired {
	enum ItemType {
		itAny,
		itMoney,
		itWeapon,
		itArmorHelm,
		itArmorBody,
		itArmorLegs,
		itArmorFist,
		itArmorShoe,
		itArmorArms
	};


	struct MapItem {
		fired::ItemType type;
		char            name[64];
		unsigned int    count;

		MapItem() {};
		MapItem(fired::ItemType _type, unsigned int _count, const char *_name);
	};
}

#endif
