#ifndef __GUI
#define __GUI


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class GUI {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;
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
		 GUI(fired::Game *_game, fired::Camera *_cam, fired::Player *_player);
		~GUI();

		void update();
		void render();
	};
}

#endif
