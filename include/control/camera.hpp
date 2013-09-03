#ifndef __CAMERA
#define __CAMERA


#include "phys.hpp"


namespace fired {
	struct Camera {
		sf::Vector2f  offset;
		sf::Vector2i  mapSize;
		sf::FloatRect viewport;
		sf::View      view;

		fired::Phys  *objToTrack;


		Camera();

		void update();
		void reset();
		bool isRectVisible(sf::FloatRect rect);
		bool isPixelVisible(sf::Vector2f pixel);
	};
}

#endif

