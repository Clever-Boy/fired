#ifndef __WIN_INVENTORY
#define __WIN_INVENTORY


#include "win_hint.hpp"


namespace fired {
	struct InventoryWindowItem {
		fired::InventoryItem  *item;
		fired::ItemType        filter;
		sf::FloatRect          rect;
		bool                   hover;


		 InventoryWindowItem(sf::Vector2f pos, fired::InventoryItem  *_item, fired::ItemType _filter);
		~InventoryWindowItem() {};

		void render(sf::Sprite *spr, sf::Text *count);
		void renderItem(sf::Text *count);
	};


	struct InventoryWindow {
		fired::Window              *win;
		fired::HintWindow          *hint;
		fired::Character           *owner;
		fired::InventoryWindowItem *inHand; 
		fired::GameSprite          *coinSprite;

		std::vector<fired::InventoryWindowItem*> items;

		sf::Texture *emptyTex;
		sf::Texture *hoverTex;
		sf::Texture *normalTex;

		sf::Sprite *emptySpr;
		sf::Sprite *hoverSpr;
		sf::Sprite *normalSpr;

		sf::Text   *moneyText;
		sf::Text   *countText;


		 InventoryWindow(fired::Character *_owner, fired::World *world);
		~InventoryWindow();

		void update(sf::Vector2f mousePos);
		void render();
		void click(sf::Vector2f mousePos);
	};
}

#endif
