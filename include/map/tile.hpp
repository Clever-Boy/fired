#ifndef __TILE
#define __TILE


#define TILE_SIZE 16.0


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "tileset.hpp"


namespace fired {
	struct MapTile {
		int tileset;
		bool isWall;
	};


	class Tile {
	private:
		sf::Vector2f pos;
		sf::Sprite  *sprite;
		sf::Color    color;

		int tileset;
		int tile;
		bool isWall;


	public:
		void set(int _tileset, bool _isWall, int x, int y);
		void render();

		void setTileset(fired::Tileset *_tileset);
		void setTile(int _tile);
		int  getIndex() { return tileset; };
		bool isSolid()  { return isWall; };
	};
}

#endif
