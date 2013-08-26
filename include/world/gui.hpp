#ifndef __GUI
#define __GUI


#include "char.hpp"


namespace fired {
	class GUI {
	private:
		fired::Player    *player;


		int          barHeight;
		int          barWidth;

		sf::Texture *barTex;
		sf::Sprite  *barSpr;

		sf::RectangleShape *bar;
		sf::String         *str;
		sf::Text           *txt;

	public:
		 GUI(fired::Player *_player);
		~GUI();

		void update();
		void render();
	};
}

#endif
