#ifndef __TILE
#define __TILE


#include "tileset.hpp"


namespace fired {
	struct MapTile {
		int tileset;
		bool isWall;
		bool isPlatform;
	};


	class Tile {
	private:
		sf::Vector2f pos;
		sf::Sprite  *sprite;
		sf::Color    color;

		int tileset;
		int tile;
		bool isWall;
		bool isPlatform;


	public:
		void set(int _tileset, bool _isWall, bool _isPlatform, int x, int y);
		void render();

		void setTileset(fired::Tileset *_tileset);
		void setTile(int _tile);
		int  getIndex() { return tileset; };
		bool isSolid()  { return isWall; };
		bool platform() { return isPlatform; };
	};
}

#endif
