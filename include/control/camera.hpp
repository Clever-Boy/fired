#ifndef __CAMERA
#define __CAMERA


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "phys.hpp"


namespace fired {
	class Camera {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		sf::Vector2f  offset;
		sf::FloatRect viewport;
		sf::View      view;

		fired::Phys  *objToTrack;

	public:
		void init(fired::Game *_game);
		void update();

		void          setTrackObj(fired::Phys *phys) { objToTrack = phys; };
		sf::Vector2f  getOffset() { return offset; };
	};
}

#endif

