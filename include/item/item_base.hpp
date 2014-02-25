/***********************************************************************
     * File       : item_base.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __ITEM_BASE
#define __ITEM_BASE


namespace fired {
	enum ItemType {
		itAny,
		itWeapon,
		itArmor,
		itAmmo
	};


	struct BaseItem {
		char               name[64];
		char               tip[64];
		unsigned int       maxStack;
		int                ID;
		int                UID;
		fired::ItemType    type;
		fired::GameSprite *sprite;
	};


	struct InventoryItem {
		fired::BaseItem *base;
		unsigned int    count;

		InventoryItem();
		InventoryItem(fired::BaseItem *_base, unsigned int _count);

		void render(sf::Vector2f pos);
	};
}

#endif
