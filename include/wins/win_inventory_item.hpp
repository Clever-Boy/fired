/***********************************************************************
     * File       : win_inventory_item.hpp
     * Created    : Jan 23, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WIN_INVENTORY_ITEM
#define __WIN_INVENTORY_ITEM


namespace fired {
	struct InventoryWindowItem {
		fired::InventoryItem  *item;
		fired::ItemType        filter;
		fired::ArmorClass      armorFilter;
		sf::FloatRect          rect;
		bool                   hover;


		 InventoryWindowItem(sf::Vector2f pos, fired::InventoryItem  *_item, fired::ItemType _filter, fired::ArmorClass _armorFilter = acNull);
		~InventoryWindowItem() {};

		void render(sf::Sprite *spr, sf::Text *count);
		void renderItem(sf::Text *count);
	};
}

#endif
