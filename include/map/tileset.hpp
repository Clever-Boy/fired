#ifndef __TILESET
#define __TILESET


#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "prototypes.hpp"


namespace fired {
	class Tileset {
		friend class Tile;


	private:
		std::vector<sf::Texture*> textures;
		std::vector<sf::Sprite*>  sprites;

		sf::Texture *maskTex;
		std::vector<sf::Sprite*> masks;


	public:
		void init();
		void deinit();
		void addTile(const char *filename);

		sf::Sprite *getTile(int index) { return sprites[index]; };
		sf::Sprite *getMask(int index) { return masks[index]; };
	};
}

#endif
