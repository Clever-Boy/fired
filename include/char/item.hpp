#ifndef __ITEM
#define __ITEM


namespace fired {
	struct BaseInventoryItem {
		char        name[32];
		sf::Sprite *sprite;


		 BaseInventoryItem() {};
		~BaseInventoryItem() {};

		void render(sf::Vector2f pos);
	};
}

#endif
