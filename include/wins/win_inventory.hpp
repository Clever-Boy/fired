#ifndef __WIN_INVENTORY
#define __WIN_INVENTORY


#include "win_base.hpp"


namespace fired {
	struct InventoryWindowItem {
		fired::InventoryItem **item;
		sf::FloatRect          rect;
		bool                   hover;


		 InventoryWindowItem(sf::Vector2f pos, fired::InventoryItem **_item);
		~InventoryWindowItem() {};

		void render(sf::Sprite *spr, sf::Text *count);
	};


	class InventoryWindow {
	private:
		fired::Window    *win;
		fired::Character *owner;

		std::vector<fired::InventoryWindowItem*> items;

		sf::Texture *emptyTex;
		sf::Texture *hoverTex;
		sf::Texture *normalTex;

		sf::Sprite *emptySpr;
		sf::Sprite *hoverSpr;
		sf::Sprite *normalSpr;

		sf::Text   *moneyText;
		sf::Text   *countText;


	public:
		 InventoryWindow(fired::Character *_owner);
		~InventoryWindow();

		void update(sf::Vector2f mousePos);
		void render();
	};
}

#endif
