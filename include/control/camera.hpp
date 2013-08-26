#ifndef __CAMERA
#define __CAMERA


#include "phys.hpp"


namespace fired {
	class Camera {
	private:
		sf::Vector2f  offset;
		sf::Vector2i  mapSize;
		sf::FloatRect viewport;
		sf::View      view;

		fired::Phys  *objToTrack;


	public:
		Camera();

		void update();
		void reset();
		bool isRectVisible(sf::FloatRect rect);

		void          setTrackObj(fired::Phys *phys)    { objToTrack = phys;  };
		void          setMapSize(sf::Vector2i _mapSize) { mapSize = _mapSize; };
		sf::Vector2f  getOffset()                       { return offset;      };
		sf::FloatRect getViewport()                     { return viewport;    };
	};
}

#endif

