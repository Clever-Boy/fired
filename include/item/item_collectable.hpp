/***********************************************************************
     * File       : item_collectable.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __ITEM_COLLECTABLE
#define __ITEM_COLLECTABLE


namespace fired {
	struct CollectableItem {
		fired::InventoryItem  item;
		fired::World         *world;
		fired::Phys           phys;


		CollectableItem(fired::InventoryItem *_item, sf::Vector2f pos, sf::Vector2f velocity, fired::World *_world);

		void update();
		void render();
	};
}

#endif
