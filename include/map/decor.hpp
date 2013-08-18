#ifndef __DECOR
#define __DECOR


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "tileset.hpp"


namespace fired {
	struct MapDecor {
		char name[16];
		sf::Vector2f pos;
	};


	struct BaseDecor {
		char name[16];
		sf::Texture *tex;
		sf::Sprite  *spr;
		sf::Vector2f size;

		 BaseDecor(const char *_name, const char *filename);
		~BaseDecor();
	};


	class Decor {
	private:
		sf::Vector2f pos;
		sf::Sprite  *sprite;
		sf::Color    color;


	public:
		Decor(fired::BaseDecor *base, sf::Vector2f _pos);

		void render();
	};
}

#endif
