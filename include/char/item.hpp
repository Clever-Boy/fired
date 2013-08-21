#ifndef __ITEM
#define __ITEM


namespace fired {
	enum ItemType {
		itMoney,
		itWeapon
	};


	struct InventoryItem {
		fired::ItemType type;
		char            name[32];
		unsigned int    count;
		sf::Sprite     *sprite;


		 InventoryItem() {};
		~InventoryItem() {};

		void render(sf::Vector2f pos);
	};


	struct CollectableItem {
		fired::InventoryItem *item;
		fired::Phys           phys;


		 CollectableItem();
		~CollectableItem() {};

		void render();
	};
}

#endif
