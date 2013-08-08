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

		sf::Texture *barTex;
		sf::Sprite  *barSpr;

		sf::Texture        *healthTex;
		sf::RectangleShape *healthSpr;

		sf::Texture *ammoTex;
		sf::Sprite  *ammoSpr;
		sf::String  *ammoCnt;
		sf::Text    *ammoTxt;

	public:
		void init(fired::Game *_game, fired::Camera *_cam, fired::Player *_player);
		void deinit();
		void update();
		void render();
	};
}

#endif