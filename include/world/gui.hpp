#ifndef __GUI
#define __GUI


#include "char.hpp"


namespace fired {
	struct GUI {
		fired::Player    *player;

		int          barHeight;
		int          barWidth;

		sf::Texture *barTex;
		sf::Sprite  *barSpr;

		sf::RectangleShape *bar;
		sf::String         *str;
		sf::Text           *txt;


		 GUI(fired::Player *_player);
		~GUI();

		void update();
		void render();
	};
}

#endif
