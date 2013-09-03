#ifndef __ITEM
#define __ITEM


namespace fired {
	struct InventoryItem {
		fired::ItemType type;
		char            name[64];
		char            caption[64];
		unsigned int    count;
		sf::Color       color;
		sf::Sprite     *sprite;


		 InventoryItem(fired::ItemType _type, unsigned int _count, const char *_name, fired::World *world);
		 InventoryItem(fired::MapItem *base, fired::World *world);
		~InventoryItem() {};

		void init(fired::ItemType _type, unsigned int _count, const char *_name, fired::World *world);
		void render(sf::Vector2f pos);
	};
}

#endif
