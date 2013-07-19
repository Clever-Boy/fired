#ifndef __MENUITEM
#define __MENUITEM

#define MENU_FONT_FILE "data/fonts/advanced_pixel-7.ttf"
#define MENU_FONT_SIZE 32
#define MENU_Y_OFFSET  1.5


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"

namespace fired {
	class MenuItem {
	private:
		fired::Game  *game;
		sf::Sprite   *sprite;
		sf::String   caption;
		sf::Text     text;
		sf::Font     *font;

		sf::Vector2f pos;

		float xOffset;

	public:
		void init(fired::Game *_game, sf::Sprite *_sprite, sf::Font *_font, const char *_caption);
		void update(float frameClock);
		void render();
	};
}
#endif
