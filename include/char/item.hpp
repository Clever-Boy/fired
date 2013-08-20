#ifndef __ITEM
#define __ITEM


namespace fired {
	struct InventoryItem {
		char        name[32];
		sf::Sprite *sprite;


		 InventoryItem() {};
		~InventoryItem() {};

		void render(sf::Vector2f pos);
	};


	struct CollectableItem {
		fired::InventoryItem *item;
		fired::Phys           phys;


		 CollectableItem() {};
		~CollectableItem() {};

		void render();
	};
}

#endif
