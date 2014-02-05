/***********************************************************************
     * File       : win_inventory.hpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WIN_INVENTORY
#define __WIN_INVENTORY


#include "win_hint.hpp"
#include "win_inventory_item.hpp"


namespace fired {
	struct InventoryWindow {
		fired::Window              *win;
		fired::HintWindow          *hint;
		fired::Character           *owner;
		fired::InventoryWindowItem *inHand;
		fired::InventoryWindowItem *trashCan;

		std::vector<fired::InventoryWindowItem*> items;

		sf::Text   *moneyText;
		sf::Text   *countText;


		 InventoryWindow(fired::Character *_owner, fired::World *world);
		~InventoryWindow();

		void update(sf::Vector2f mousePos);
		void render();
		void click(sf::Vector2f mousePos);
		void clickRight(sf::Vector2f mousePos);
	};
}

#endif
