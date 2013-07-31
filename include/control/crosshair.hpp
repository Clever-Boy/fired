#ifndef __CROSSHAIR
#define __CROSSHAIR


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class Crosshair {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;
		fired::Camera    *cam;
		fired::Phys      *owner;

		float angle;
		sf::Vector2f pos;
		sf::Texture *crosshairTex;
		sf::Sprite  *crosshairCur;


	public:
		void init(fired::Game *_game, fired::Camera *_cam, fired::Phys *_owner);
		void deinit();
		void update(float distance);
		void render();

		void  processEvent(sf::Event event);
		float getAngle() { return angle; };
	};
}

#endif
