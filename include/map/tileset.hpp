#ifndef __TILESET
#define __TILESET


#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "prototypes.hpp"


namespace fired {
	class Tileset {
		friend class Tile;


	private:
		sf::Texture *texture;
		std::vector<sf::Sprite*> tiles;


	public:
		void init(const char *textureFile);
		void deinit();

		sf::Sprite *getTile(int index) { return tiles[index]; };
	};
}

#endif
