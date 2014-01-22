/***********************************************************************
     * File       : collectable_item.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __COLLECTABLE_ITEM
#define __COLLECTABLE_ITEM


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
