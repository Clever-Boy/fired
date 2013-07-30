#ifndef __TILE
#define __TILE


#define TILE_SIZE        16.0
#define TILE_SIZE_ORIGIN 32.0


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct MapTile {
		int tileset;
	};


	class Tile {
	private:
		fired::Tileset *tileset;

		sf::Vector2f pos;
		int tilesetIdx;
		int tile;


	public:
		void init(int _tileset, int x, int y);
		void deinit();
		void render(sf::RenderWindow *app);

		void setTileset(fired::Tileset *_tileset) { tileset = _tileset; };
		int  getIndex()   { return tilesetIdx; };
		bool isSolid()    { return tileset; };
	};
}

#endif
