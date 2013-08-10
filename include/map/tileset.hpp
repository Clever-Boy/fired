#ifndef __TILESET
#define __TILESET


#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "prototypes.hpp"


namespace fired {
	class Tileset {
		friend class Tile;


	private:
		sf::Texture *maskTex;
		std::vector<sf::Texture*> textures;
		std::vector<sf::Sprite*>  sprites;


	public:
		void init();
		~Tileset();

		void addTile(const char *filename);

		sf::Sprite *getTile(int index) { return sprites[index]; };
	};
}

#endif
