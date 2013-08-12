#ifndef __GUI
#define __GUI


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class GUI {
	private:
		fired::Camera    *cam;
		fired::Player    *player;


		int          barHeight;
		int          barWidth;

		sf::Texture *barTex;
		sf::Sprite  *barSpr;

		sf::RectangleShape *bar;
		sf::String         *str;
		sf::Text           *txt;

	public:
		 GUI(fired::Camera *_cam, fired::Player *_player);
		~GUI();

		void update();
		void render();
	};
}

#endif
