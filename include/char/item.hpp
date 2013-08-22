#ifndef __ITEM
#define __ITEM


#define ITEM_SPEED 100.0f


namespace fired {
	enum ItemType {
		itMoney,
		itWeapon
	};


	struct LootItem {
		fired::ItemType type;
		char            name[32];

		unsigned int    minCount;
		unsigned int    maxCount;
		float           probability;


		LootItem(fired::ItemType _type, const char *_name, unsigned int _minCount, unsigned int _maxCount, float _probability);
	};


	struct InventoryItem {
		fired::ItemType type;
		char            name[32];
		char            caption[32];
		unsigned int    count;
		sf::Sprite     *sprite;


		 InventoryItem(fired::ItemType _type, unsigned int _count, const char *_name, fired::World *world);
		~InventoryItem() {};

		void render(sf::Vector2f pos);
	};


	struct CollectableItem {
		fired::InventoryItem *item;
		fired::Phys           phys;


		 CollectableItem(fired::InventoryItem *_item, sf::Vector2f pos, sf::Vector2f velocity);
		~CollectableItem() {};

		void update();
		void render();
	};
}

#endif
