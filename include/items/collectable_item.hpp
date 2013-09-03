#ifndef __COLLECTABLE_ITEM
#define __COLLECTABLE_ITEM


namespace fired {
	struct CollectableItem {
		fired::InventoryItem *item;
		fired::World         *world;
		fired::Phys           phys;


		 CollectableItem(fired::InventoryItem *_item, sf::Vector2f pos, sf::Vector2f velocity, fired::World *_world);
		~CollectableItem() {};

		void update();
		void render();
	};
}

#endif
