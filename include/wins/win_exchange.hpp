#ifndef __WIN_EXCHANGE
#define __WIN_EXCHANGE


#include "win_inventory.hpp"
#include "map.hpp"

namespace fired {
	class ExchangeWindow {
	private:
		fired::Window              *win;
		fired::Character           *owner;
		fired::InventoryWindowItem *inHand; 

		std::vector<fired::InventoryWindowItem*> items;
		std::vector<fired::InventoryWindowItem*> exchange;

		sf::Texture *emptyTex;
		sf::Texture *hoverTex;
		sf::Texture *normalTex;

		sf::Sprite *emptySpr;
		sf::Sprite *hoverSpr;
		sf::Sprite *normalSpr;

		sf::Text   *moneyText;
		sf::Text   *countText;


	public:
		 ExchangeWindow(fired::Character *_owner);
		~ExchangeWindow();

		void update(sf::Vector2f mousePos);
		void render();
		void click(sf::Vector2f mousePos);

		void init(fired::MapObjectCollector *collector);
	};
}

#endif
